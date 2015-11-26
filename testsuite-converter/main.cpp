
#include <iosfwd>
#include <string>
#include <fstream>
#include <sexpr_parsing/SExpr.h>
#include <sexpr_parsing/SExprParser.h>
#include <iostream>
#include <map>
#include <list>
#include <boost/filesystem.hpp>

using namespace wasm_module;
using namespace wasm_module::sexpr;


class UnknownAssertValue : public std::exception {};
class NoModuleWithExport : public std::exception {};

class ModuleWrapper {
public:
    SExpr moduleExpr_;
    std::map<std::string, std::string> exports;

    SExpr positiveExpr_;
    std::vector<SExpr> negativeExprs_;

    ModuleWrapper(const SExpr& moduleExpr) {
        moduleExpr_ = moduleExpr;

        std::list<std::size_t> positionsToRemove;
        for (std::size_t i = 0; i < moduleExpr_.children().size(); i++) {
            if (moduleExpr[i].hasChildren() && moduleExpr_[i][0].value() == "export") {
                positionsToRemove.push_back(i);
                exports[moduleExpr[i][1].value()] = moduleExpr[i][2].value();
            }
        }
        while (!positionsToRemove.empty()) {
            moduleExpr_.removeChild(positionsToRemove.back());
            positionsToRemove.pop_back();
        }
    }

    bool hasPositiveChecks() {
        return positiveExpr_.hasChildren();
    }

    void addPositiveCheck(const SExpr& expr) {
        positiveExpr_.addChild(expr);
    }

    void addNegativeCheck(const SExpr& expr) {
        negativeExprs_.push_back(expr);
    }

    void addMain(SExpr& module, const SExpr& mainContent) {
        SExpr mainExpr;
        mainExpr.addChild("func");
        mainExpr.addChild("main");
        mainExpr.addChild(mainContent);
        module.addChild(mainExpr);
    }

    SExpr getPositiveTestSource() {
        SExpr result = moduleExpr_;

        addMain(result, positiveExpr_);

        return result;
    }

    std::vector<SExpr> getNegativeSources() {
        std::vector<SExpr> result;
        result.reserve(negativeExprs_.size());

        for (const SExpr& expr : negativeExprs_) {
            SExpr output = moduleExpr_;
            addMain(output, expr);
            result.push_back(output);
        }

        return result;
    }


    bool hasExport(std::string expo) {
        return exports.find(expo) != exports.end();
    }

    std::string getExport(std::string expo) {
        return exports.find(expo)->second;
    }
};

class WastTestTransformer {
    std::string baseName;
    std::vector<ModuleWrapper> modules;
    sexpr::SExpr mainExpr;

    void writeSExpr(std::string directoryPath, const SExpr& sexpr, std::string fileName) {

        boost::filesystem::path directory(directoryPath);
        boost::filesystem::create_directories(directory);

        boost::filesystem::path absolutePath = directory / (fileName + ".wasm");

        std::ofstream out(absolutePath.string());

        out << sexpr.toString();
        out.close();
    }

public:
    WastTestTransformer(const std::string& wastPath) {
        boost::filesystem::path p(wastPath);

        baseName = p.stem().string();

        std::ifstream moduleFile(wastPath);
        std::string moduleData((std::istreambuf_iterator<char>(moduleFile)),
                               std::istreambuf_iterator<char>());
        sexpr::CharacterStream stream(moduleData);

        mainExpr = sexpr::SExprParser(stream).parse(true);

        for (const SExpr& expr : mainExpr.children()) {
            if (expr.hasChildren()) {
                if (expr[0].value() == "module") {
                    modules.push_back(ModuleWrapper(expr));
                }
            }
        }
    }

    ModuleWrapper& getModule(std::string exportName) {
        for(ModuleWrapper& moduleWrapper : modules) {
            if (moduleWrapper.hasExport(exportName)) {
                return moduleWrapper;
            }
        }
        std::cerr << exportName << std::endl;
        throw NoModuleWithExport();
    }

    ModuleWrapper& invokeToCall(SExpr&invoke) {
        ModuleWrapper& wrapper = getModule(invoke[1].value());

        std::string functionName = wrapper.getExport(invoke[1].value());

        invoke[0] = SExpr("call");
        invoke[1] = SExpr(functionName);

        return wrapper;
    }

    void generateOutput() {
        int testNumber = 1;
        for (SExpr expr : mainExpr.children()) {
            if (!expr.hasChildren())
                continue;
            if (expr[0].value() == "invoke") {
                ModuleWrapper& wrapper = invokeToCall(expr);
                wrapper.addPositiveCheck(expr);
            } else if (expr[0].value() == "assert_return") {
                SExpr invokeExpr = expr[1];

                ModuleWrapper& wrapper = invokeToCall(invokeExpr);


                std::string dataType;

                if (expr.children().size() <= 2) {
                    std::cout << "warning - can't handle this assert_return: " << expr.toString() << std::endl;
                } else {
                    if (expr[2][0].value() == "i32.const") {
                        dataType = "i32";
                    } else if (expr[2][0].value() == "i64.const") {
                        dataType = "i64";
                    } else if (expr[2][0].value() == "f32.const") {
                        dataType = "f32";
                    } else if (expr[2][0].value() == "f64.const") {
                        dataType = "f64";
                    } else {
                        std::cerr << expr[2][0].value() << std::endl;
                        throw UnknownAssertValue();
                    }

                    if (dataType[0] == 'i') {
                        SExpr ifExpr;
                        ifExpr.addChild("if_else");

                        SExpr eqExpr;
                        eqExpr.addChild(dataType + ".eq");
                        eqExpr.addChild(invokeExpr);
                        eqExpr.addChild(expr[2]);

                        ifExpr.addChild(eqExpr);
                        ifExpr.addChild();
                        ifExpr.addChild(SExprParser::parseString("(unreachable)"));
                        wrapper.addPositiveCheck(ifExpr);
                    } else {
                        if (dataType == "f32") {
                            SExpr ifExpr = SExprParser::parseString("(if_else (i32.eq (i32.reinterpret/f32) (i32.reinterpret/f32)) () (unreachable) )");
                            ifExpr[0][1][1].addChild(invokeExpr);
                            ifExpr[0][1][2].addChild(expr[2]);
                            wrapper.addPositiveCheck(ifExpr);
                        } else if (dataType == "f64") {
                            SExpr ifExpr = SExprParser::parseString("(if_else (i64.eq (i64.reinterpret/f64) (i64.reinterpret/f64)) () (unreachable) )");
                            ifExpr[0][1][1].addChild(invokeExpr);
                            ifExpr[0][1][2].addChild(expr[2]);
                            wrapper.addPositiveCheck(ifExpr);
                        } else {
                            assert(false);
                        }
                    }

                }

            } else if (expr[0].value() == "assert_return_nan") {
                // TODO
            } else if (expr[0].value() == "assert_trap") {
                SExpr invoke = expr[1];
                ModuleWrapper& wrapper = getModule(invoke[1].value());

                std::string functionName = wrapper.getExport(invoke[1].value());

                invoke[0] = SExpr("call");
                invoke[1] = SExpr(functionName);

                //writeAST("negative/trap/", testNumber, expr, invoke[1].value(), wrapper);
            } else if (expr[0].value() == "assert_invalid") {
                writeSExpr("negative/parse/", expr, baseName + std::to_string(testNumber));
            } else if (expr[0].value() == "module") {
                // TODO
                testNumber--;
            } else {
                std::cerr << "warning - unknown top level expr: " << expr.toString() << std::endl;
            }
            testNumber++;
        }

        for(ModuleWrapper& moduleWrapper : modules) {
            SExpr output = moduleWrapper.getPositiveTestSource();
            writeSExpr("positive/", output, baseName);
        }

    }

};

int main(int argv, char** argc) {

    if (argv <= 1) {
        std::cerr << "testsuite-converter needs at least one path to a wast test file as an argument" << std::endl;
        return 1;
    }

    for (int i = 1; i < argv; i++) {
        std::string modulePath = argc[i];

        std::cout << "Processing " << modulePath << std::endl;
        try {

            WastTestTransformer transformer(modulePath);
            transformer.generateOutput();
            std::cout << "Done!" << std::endl;
        } catch (const std::exception& ex) {
            std::cerr << "Got exception: " << typeid(ex).name() << " - what(): " << ex.what() << std::endl;
        }

    }

    return 0;
}
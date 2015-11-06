
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

    void addMain(SExpr& module, const SExpr& mainContent) {
        SExpr mainExpr;
        mainExpr.addChild("func");
        mainExpr.addChild("main");
        mainExpr.addChild(mainContent);
        module.addChild(mainExpr);
    }

    void writeAST(std::string directoryPath, int testNumber, SExpr ast, std::string functionName, ModuleWrapper& module) {

        for (std::size_t i = 0; i < functionName.size(); i++) {
            if (functionName[i] == '$')
                functionName[i] = '_';
        }

        boost::filesystem::path directory(directoryPath);
        boost::filesystem::create_directories(directory);

        directory /= (baseName + std::string("_no") + std::to_string(testNumber)) + std::string("_") + functionName + ".wasm";

        sexpr::SExpr moduleExpr = module.moduleExpr_;

        addMain(moduleExpr, ast);

        std::ofstream out(directory.string());

        out << moduleExpr.toString();
        out.close();
    }

    void writeSExpr(std::string directoryPath, int testNumber, const SExpr& expr) {
        boost::filesystem::path directory(directoryPath);
        boost::filesystem::create_directories(directory);

        directory /= (baseName + std::string("_no") + std::to_string(testNumber)) + ".wasm";

        std::ofstream out(directory.string());

        out << expr.toString();
        out.close();
    }

public:
    WastTestTransformer(std::string wastPath) {
        boost::filesystem::path p(wastPath);

        baseName = p.stem().string();

        std::ifstream moduleFile(wastPath);
        std::string moduleData((std::istreambuf_iterator<char>(moduleFile)),
                               std::istreambuf_iterator<char>());
        sexpr::CharacterStream stream(moduleData);

        mainExpr = sexpr::SExprParser(stream).parse(true);

        for (const SExpr& expr : mainExpr.children()) {
            if (expr[0].value() == "module") {
                modules.push_back(ModuleWrapper(expr));
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

    void generateOutput() {
        int testNumber = 1;
        for (SExpr expr : mainExpr.children()) {
            if (expr[0].value() == "invoke") {
                ModuleWrapper& wrapper = getModule(expr[1].value());

                std::string functionName = wrapper.getExport(expr[1].value());

                expr[0] = SExpr("call");
                expr[1] = SExpr(functionName);

                writeAST("positive/", testNumber, expr, expr[1].value(), wrapper);
            } else if (expr[0].value() == "assert_return") {
                SExpr invokeExpr = expr[1];

                ModuleWrapper& wrapper = getModule(invokeExpr[1].value());

                std::string functionName = wrapper.getExport(invokeExpr[1].value());

                invokeExpr[0] = SExpr("call");
                invokeExpr[1] = SExpr(functionName);

                SExpr ifExpr;
                ifExpr.addChild("if");

                std::string dataType;

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

                SExpr eqExpr;
                eqExpr.addChild(dataType + ".eq");
                eqExpr.addChild(invokeExpr);
                eqExpr.addChild(expr[2]);

                ifExpr.addChild(eqExpr);
                ifExpr.addChild();
                ifExpr.addChild(SExprParser::parseString("(i32.div_s (i32.const 1) (i32.const 0))"));

                writeAST("positive/", testNumber, ifExpr, invokeExpr[1].value(), wrapper);
            } else if (expr[0].value() == "assert_return_nan") {
                // TODO
            } else if (expr[0].value() == "assert_trap") {
                ModuleWrapper& wrapper = getModule(expr[1].value());

                std::string functionName = wrapper.getExport(expr[1].value());

                expr[0] = SExpr("call");
                expr[1] = SExpr(functionName);

                writeAST("negative/trap/", testNumber, expr, expr[1].value(), wrapper);
            } else if (expr[0].value() == "assert_invalid") {
                writeSExpr("negative/parse/", testNumber, expr[1]);
            } else if (expr[0].value() == "module") {
                // TODO
                testNumber--;
            } else {
                std::cerr << "warning - unknown top level expr: " << expr.toString() << std::endl;
            }
            testNumber++;
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
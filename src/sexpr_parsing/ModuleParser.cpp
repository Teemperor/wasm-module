/*
 * Copyright 2015 WebAssembly Community Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ModuleParser.h"
#include "FunctionParser.h"


namespace wasm_module { namespace sexpr {


        ModuleParser::ModuleParser(const SExpr& moduleExpr) {
            for(unsigned i = 1; i < moduleExpr.children().size(); i++) {
                const SExpr& expr = moduleExpr[i];
                const std::string& typeName = expr[0].value();
                if (typeName == "import") {
                    parseImport(expr);
                } else if (typeName == "func") {
                    Function* function = &FunctionParser::parse(expr, module_->context());
                    module_->context().functionTable().addFunctionSignature(*function);
                    module_->addFunction(function, true);
                } else {
                    throw UnknownModuleChild(typeName);
                }
            }
        }

        void ModuleParser::parseImport(const SExpr& importExpr) {
            if (importExpr.children().size() != 5) {
                throw MalformedImportStatement(importExpr.toString());
            } else {
                if (importExpr[0] != "import") {
                    throw MalformedImportStatement(importExpr.toString());
                }

                std::string importName = importExpr[1].value();
                std::string moduleName = importExpr[2].value();
                std::string functionName = importExpr[3].value();

                const Type* returnType = Void::instance();

                std::vector<const Type*> parameters;

                for (uint32_t i = 4; i < importExpr.children().size(); i++) {
                    const SExpr& subExpr = importExpr[i];

                    if (subExpr[0].value() == "param") {
                        parameters.push_back(Types::getByName(subExpr[1].value()));
                    } else if (subExpr[0].value() == "return") {
                        if (returnType != Void::instance()) {
                            throw MultipleReturnTypesInImport(importExpr.toString());
                        }

                        returnType = Types::getByName(subExpr[1].value());
                    } else {
                        throw UnknownImportExpressionChild(subExpr.value());
                    }
                }

                ModuleImport moduleImport(importName, moduleName, FunctionSignature(functionName, returnType, parameters, true));
                module_->addImport(moduleImport);
            }
        }
    }}
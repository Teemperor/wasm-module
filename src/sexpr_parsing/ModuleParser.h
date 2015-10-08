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

#ifndef WASMINT_MODULEPARSER_H
#define WASMINT_MODULEPARSER_H

#include <Module.h>
#include "CharacterStream.h"
#include "SExpr.h"

namespace wasm_module { namespace sexpr {


    ExceptionMessage(UnknownModuleChild)
    ExceptionMessage(MalformedImportStatement)
    ExceptionMessage(MissingModuleKeyword)

    class ModuleParser {

        Module* module_  = new Module();

        void parseImport(const SExpr& importExpr) {
            if (importExpr.children().size() != 5) {
                throw MalformedImportStatement(importExpr.toString());
            } else {
                if (importExpr[0] != "import") {
                    throw MalformedImportStatement(importExpr.toString());
                }

                std::string importName = importExpr[1].value();
                std::string moduleName = importExpr[2].value();
                std::string functionName = importExpr[3].value();

                ModuleImport moduleImport(importName, moduleName, functionName);
                module_->addImport(moduleImport);
            }
        }

        ModuleParser(const SExpr& moduleExpr) {
            for(unsigned i = 1; i < moduleExpr.children().size(); i++) {
                const SExpr& expr = moduleExpr[i];
                const std::string& typeName = expr[0].value();
                if (typeName == "import") {
                    parseImport(expr);
                } else if (typeName == "func") {

                } else {
                    throw UnknownModuleChild(typeName);
                }
            }
        }

        Module* getParsedModule() {
            return module_;
        }

    public:

        static Module* parse(const SExpr& expr) {
            ModuleParser parser(expr);
            return parser.getParsedModule();
        }

    };

}}


#endif //WASMINT_MODULEPARSER_H

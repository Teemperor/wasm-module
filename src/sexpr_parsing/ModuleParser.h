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

    class ModuleParser {

        Module* module_;

        void parseImport(const SExpr& moduleExpr) {

        }

        ModuleParser(const SExpr& moduleExpr) {
            for(const SExpr& expr : moduleExpr.children()) {
                const std::string& typeName = expr[0].value();
                if (typeName == "import") {
                    parseImport(expr[0]);
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

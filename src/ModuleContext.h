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

#ifndef WASMINT_MODULECONTEXT_H
#define WASMINT_MODULECONTEXT_H


#include "TypeTable.h"
#include "OpcodeTable.h"
#include "FunctionTable.h"
#include "GlobalTable.h"

namespace wasm_module {

    class ModuleContext {

        OpcodeTable opcodeTable_;
        TypeTable typeTable_;
        FunctionTable functionTable_;
        GlobalTable globalTable_;

    public:
        ModuleContext() {

        }

        ModuleContext(OpcodeTable &opcodeTable, TypeTable &typeTable, FunctionTable &functionTable,
                      GlobalTable &globalTable)
                : opcodeTable_(opcodeTable), typeTable_(typeTable), functionTable_(functionTable),
                  globalTable_(globalTable) {

        }

        OpcodeTable &opcodeTable() {
            return opcodeTable_;
        }

        TypeTable &typeTable() {
            return typeTable_;
        }

        FunctionTable &functionTable() {
            return functionTable_;
        }

        GlobalTable &globalTable() {
            return globalTable_;
        }

    };

}

#endif //WASMINT_MODULECONTEXT_H

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
#include "ModuleImport.h"

namespace wasm_module {

    ExceptionMessage(NoImportWithName)
    ExceptionMessage(AlreadyImportWithName)

    class ModuleContext {

        std::map<std::string, ModuleImport> importsByImportName_;
        OpcodeTable opcodeTable_;
        TypeTable typeTable_;
        FunctionTable functionTable_;
        GlobalTable globalTable_;
        std::string name_;

    public:
        ModuleContext() {
            name_ = "UnknownModule" + std::to_string(rand());
        }

        ModuleContext(OpcodeTable &opcodeTable, TypeTable &typeTable, FunctionTable &functionTable,
                      GlobalTable &globalTable)
                : opcodeTable_(opcodeTable), typeTable_(typeTable), functionTable_(functionTable),
                  globalTable_(globalTable) {
            name_ = "UnknownModule" + std::to_string(rand());

        }

        void addImport(const ModuleImport& moduleImport) {
            if (importsByImportName_.find(moduleImport.importName()) == importsByImportName_.end()) {
                importsByImportName_[moduleImport.importName()] = moduleImport;
            } else {
                throw AlreadyImportWithName(moduleImport.importName());
            }
        }

        const ModuleImport& getImport(const std::string& importName) const {
            auto iter = importsByImportName_.find(importName);

            if (iter != importsByImportName_.end()) {
                return iter->second;
            } else {
                throw NoImportWithName(importName);
            }
        }

        const std::string& name() const {
            return name_;
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

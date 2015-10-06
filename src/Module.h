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

#ifndef INTERPRETER_MODULE_H
#define INTERPRETER_MODULE_H

#include <string>
#include "binary_parsing/ByteStream.h"
#include "Section.h"
#include "OpcodeTable.h"
#include "TypeTable.h"
#include "ModuleContext.h"
#include <vector>

namespace wasm_module {

    class Module {

        std::vector<Section *> sections_;
        ModuleContext context_;
        std::vector<std::string> requiredModules_;

    public:
        Module(ModuleContext &context, std::vector<Section *> sections,
               std::vector<std::string> requiredModules)
                : sections_(sections), context_(context), requiredModules_(requiredModules) {
        }

        virtual ~Module() {
            for (Section* section : sections_) {
                delete section;
            }
        }

        std::vector<Function *> functions() {
            std::vector<Function *> result;
            for (Section *section : sections_) {
                std::vector<Function *> sectionFunctions = section->functions();
                for (Function *function : sectionFunctions) {
                    result.push_back(function);
                }
            }
            return result;
        }

        std::vector<Section *> sections() {
            return sections_;
        }

        OpcodeTable &opcodeTable() {
            return context_.opcodeTable();
        }

        TypeTable &typeTable() {
            return context_.typeTable();
        }

        std::vector<Global> globals() {
            return context_.globalTable().internalGlobals();
        }

        std::vector<std::string> requiredModules() {
            return requiredModules_;
        }

    };

}

#endif //INTERPRETER_MODULE_H

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

#include "Module.h"
#include <instructions/NativeInstruction.h>
#include <Function.h>

namespace wasm_module {

    void Module::addFunction(std::string name, const Type* returnType, std::vector<const Type*> parameterTypes, std::function<Variable(std::vector<Variable>)> givenFunction) {
        FunctionContext context(name, returnType, parameterTypes, {}, false);
        Function* function = new Function(context, new NativeInstruction(givenFunction, returnType, parameterTypes));
        functions_.push_back(function);
        functionsToDelete_.push_back(function);
    }

    Module::Module(ModuleContext &context, std::vector<Section *> sections,
                   std::vector<std::string> requiredModules)
            : sections_(sections), context_(context), requiredModules_(requiredModules) {
        for (Section *section : sections_) {
            std::vector<Function *> sectionFunctions = section->functions();
            for (Function *function : sectionFunctions) {
                functions_.push_back(function);
            }
        }
    }
}
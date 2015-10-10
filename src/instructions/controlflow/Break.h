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

#ifndef WASMINT_BREAK_H
#define WASMINT_BREAK_H


#include <instructions/Instruction.h>
#include <types/Void.h>

namespace wasm_module {

    class CalledBreak {
    };

    class Break : public Instruction {
    public:
        virtual std::vector<const Type*> childrenTypes() override {
            return {};
        }

        virtual std::string name() {
            return "break";
        }

        virtual const Type* returnType() override {
            return Void::instance();
        }
    };
}


#endif //WASMINT_BREAK_H

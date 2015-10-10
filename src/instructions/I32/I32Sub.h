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

#ifndef WASMINT_I32SUB_H
#define WASMINT_I32SUB_H


#include <instructions/Instruction.h>
#include <types/Int32.h>

namespace wasm_module {

    class I32Sub : public Instruction {

    public:
        virtual std::vector<const Type*> childrenTypes() {
            return {Int32::instance(), Int32::instance()};
        }

        virtual std::string name() {
            return "int32.sub";
        }


        virtual const Type* returnType() {
            return Int32::instance();
        }
    };
}

#endif //WASMINT_I32SUB_H

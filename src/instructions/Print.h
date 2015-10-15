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

#ifndef WASMINT_PRINT_H
#define WASMINT_PRINT_H

#include <instructions/Instruction.h>
#include <iostream>
#include <types/Int32.h>
#include <types/Void.h>

namespace wasm_module {

    class Print : public Instruction {
    public:
        virtual const std::vector<const Type*>& childrenTypes() const override {
            static std::vector<const Type*> chTypes_ = {Int32::instance()};;
            return chTypes_;
        }

        virtual const std::string& name() const override {
            static std::string name_ = "print";
            return name_;
        }

        virtual const Type* returnType() const override {
            return Void::instance();
        }


        virtual InstructionId::Value id() const {
            return InstructionId::Print;
        }
    };

}

#endif //WASMINT_PRINT_H

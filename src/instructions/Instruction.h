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

#ifndef WASMINT_OPCODE_H
#define WASMINT_OPCODE_H


#include <cstdint>
#include <vector>

#include "types/Type.h"
#include "Variable.h"

namespace wasm_module {

    class InstructionState;

    class Instruction {

        std::vector<Instruction *> children_;

    public:
        virtual ~Instruction() {
            for (Instruction *child : children()) {
                delete child;
            }
        }

        virtual void children(const std::vector<Instruction*>& newChildren) {
            children_ = newChildren;
        }

        std::vector<Instruction *> children() {
            return children_;
        }

        virtual std::string name() = 0;

        virtual std::vector<const Type *> childrenTypes() = 0;

        virtual const Type* returnType() = 0;
    };
}

#endif //WASMINT_OPCODE_H

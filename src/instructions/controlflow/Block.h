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

#ifndef WASMINT_BLOCK_H
#define WASMINT_BLOCK_H


#include <instructions/Instruction.h>
#include <binary_parsing/ByteStream.h>
#include <types/Void.h>
#include <sexpr_parsing/SExpr.h>

namespace wasm_module {


    class Block : public Instruction {

        uint32_t amountOfChildren;

    public:
        Block(binary::ByteStream &stream) {
            amountOfChildren = stream.popULEB128();
        }
        Block(const sexpr::SExpr& expr) {
        }

        virtual std::string name() {
            return "block";
        }

        virtual std::vector<Type *> childrenTypes() {
            std::vector<Type *> result;
            for (uint32_t i = 0; i < amountOfChildren; i++) {
                result.push_back(Void::instance());
            }
            return result;
        }

        virtual Type *returnType() {
            return Void::instance();
        }
    };

}

#endif //WASMINT_BLOCK_H

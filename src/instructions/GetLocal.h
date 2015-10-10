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

#ifndef WASMINT_GETLOCAL_H
#define WASMINT_GETLOCAL_H


#include <instructions/Instruction.h>
#include <binary_parsing/ByteStream.h>
#include <FunctionContext.h>
#include <sexpr_parsing/SExpr.h>

namespace wasm_module {

    class GetLocal : public Instruction {

        const Type* returnType_;

    public:
        uint32_t localIndex;

        GetLocal(binary::ByteStream &stream, FunctionContext &context) {
            localIndex = stream.popULEB128();
            returnType_ = context.locals().at(localIndex);
        }

        GetLocal(const sexpr::SExpr& expr, FunctionContext &context) {
            localIndex = context.variableNameToIndex(expr[1].value());
            returnType_ = context.locals().at(localIndex);
        }

        virtual std::string name() {
            return "get_local";
        }

        virtual std::vector<const Type*> childrenTypes() override {
            return {};
        }

        virtual const Type* returnType() override {
            return returnType_;
        }
    };

}

#endif //WASMINT_GETLOCAL_H

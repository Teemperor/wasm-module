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

#ifndef WASMINT_SETLOCAL_H
#define WASMINT_SETLOCAL_H

#include <cstdint>
#include <instructions/Instruction.h>
#include <binary_parsing/ByteStream.h>
#include <types/Int32.h>
#include <FunctionContext.h>
#include <sexpr_parsing/SExpr.h>

namespace wasm_module {

    class SetLocal : public Instruction {

        Type *expectedType;

    public:
        uint32_t localIndex;

        SetLocal(binary::ByteStream &stream, FunctionContext &functionContext) {
            localIndex = stream.popULEB128();
            expectedType = functionContext.pureLocals().at(localIndex);
        }

        SetLocal(const sexpr::SExpr& expr, FunctionContext &context) {
            localIndex = context.variableNameToIndex(expr[1].value());
            expectedType = context.pureLocals().at(localIndex);
        }


        virtual std::string name() {
            return "set_local";
        }

        virtual std::vector<Type *> childrenTypes() {
            return {expectedType};
        }

        virtual Type *returnType() {
            return expectedType;
        }
    };

}

#endif //WASMINT_SETLOCAL_H

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

#ifndef WASMINT_FUNCTIONCALL_H
#define WASMINT_FUNCTIONCALL_H


#include <instructions/Instruction.h>
#include <ModuleContext.h>
#include <sexpr_parsing/SExpr.h>

namespace wasm_module {

    class Module;

    class FunctionCall : public Instruction {

    public:
        std::string moduleName;
        FunctionSignature functionSignature;

        FunctionCall(binary::ByteStream &stream, ModuleContext &context) {
            functionSignature = context.functionTable().getFunctionSignature(stream.popULEB128());
            moduleName = context.name();
        }

        FunctionCall(const sexpr::SExpr& expr, ModuleContext &context) {
            if (context.functionTable().hasFunctionSignature(expr[1].value())) {
                functionSignature = context.functionTable().getFunctionSignature(expr[1].value());
                moduleName = context.name();
            } else {
                auto& import = context.getImport(expr[1].value());
                functionSignature = import.signature();
                moduleName = import.module();
            }
        }

        virtual std::string name() {
            return "invoke";
        }

        virtual std::vector<Type *> childrenTypes() {
            return functionSignature.parameters();
        }

        virtual Type *returnType() {
            return functionSignature.returnType();
        }
    };
}

#endif //WASMINT_FUNCTIONCALL_H

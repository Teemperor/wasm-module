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

#ifndef WASMINT_FUNCTION_H
#define WASMINT_FUNCTION_H

#include <string>
#include <vector>

#include "types/Type.h"
#include "Variable.h"
#include "FunctionSignature.h"
#include "FunctionContext.h"
#include <memory>
#include <instructions/Instruction.h>

namespace wasm_module {

    class Instruction;

    class Function : public FunctionContext {

        /**
     * The AST of this function which contains all instructions of this function.
     */
        Instruction *mainInstruction_;

    public:
        Function(FunctionContext &context, Instruction *mainInstruction);

        virtual ~Function();

        Instruction *mainInstruction() {
            return mainInstruction_;
        }
    };

}

#endif //WASMINT_FUNCTION_H

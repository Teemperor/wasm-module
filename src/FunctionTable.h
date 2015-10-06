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

#ifndef WASMINT_FUNCTIONTABLE_H
#define WASMINT_FUNCTIONTABLE_H

#include <cstdint>
#include <string>
#include <map>
#include "FunctionSignature.h"
#include "ExceptionWithMessage.h"

namespace wasm_module {

    ExceptionMessage(UnknownLocalFunctionId)

/**
 * Maps local function ids to function signatures.
 */
    class FunctionTable {

        std::vector<FunctionSignature> functionNames_;

    public:
        FunctionTable() {
        }

        void addFunctionSignature(FunctionSignature signature) {
            functionNames_.push_back(signature);
        }

        FunctionSignature getFunctionSignature(uint32_t localFunctionId) {
            if (localFunctionId > functionNames_.size())
                throw UnknownLocalFunctionId(std::to_string(localFunctionId));
            return functionNames_[localFunctionId];
        }
    };

}

#endif //WASMINT_FUNCTIONTABLE_H

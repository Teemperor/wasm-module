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

#ifndef WASMINT_FUNCTIONSIGNATURE_H
#define WASMINT_FUNCTIONSIGNATURE_H

#include <string>
#include <vector>
#include <types/Void.h>

#include "types/Type.h"
#include "Variable.h"

namespace wasm_module {

/**
 * Contains all information that are relevant to an caller of the given function.
 */
    class FunctionSignature {

        std::string name_;
        Type *returnType_ = Void::instance();
        std::vector<Type *> parameterTypes_;
        bool isExported_ = false;

    public:
        FunctionSignature() {

        }

        FunctionSignature(std::string name, Type *returnType,
                          std::vector<Type *> parameterTypes, bool exported)
                : name_(name), returnType_(returnType), parameterTypes_(parameterTypes),
                  isExported_(exported) {
        }

        Type *returnType() {
            return returnType_;
        }

        std::vector<Type *> parameters() {
            return parameterTypes_;
        }


        std::string name() {
            return name_;
        }

        bool isExported() {
            return isExported_;
        }
    };

}

#endif //WASMINT_FUNCTIONSIGNATURE_H

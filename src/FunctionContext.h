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

#ifndef WASMINT_FUNCTIONCONTEXT_H
#define WASMINT_FUNCTIONCONTEXT_H


#include "types/Type.h"
#include "FunctionSignature.h"
#include <vector>

/**
 * The context of a function. This contains all information that are needed to
 * create the instructions in the AST of the related function.
 */
class FunctionContext : public FunctionSignature {

    std::vector<Type*> locals_;

public:
    FunctionContext() {
    }

    FunctionContext(std::string name, Type* returnType, std::vector<Type*> parameterTypes,
                    std::vector<Type*> locals, bool exported)
            : locals_(locals), FunctionSignature(name, returnType, parameterTypes, exported) {

    }

    std::vector<Type*> pureLocals() {
        return locals_;
    }

    std::vector<Type*> locals() {
        std::vector<Type*> result;

        for(Type* type : parameters()) {
            result.push_back(type);
        }

        for(Type* type : pureLocals()) {
            result.push_back(type);
        }
        return result;
    }
};


#endif //WASMINT_FUNCTIONCONTEXT_H

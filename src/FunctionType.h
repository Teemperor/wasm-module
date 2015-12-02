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

#ifndef WASMINT_FUNCTIONTYPE_H
#define WASMINT_FUNCTIONTYPE_H

#include <types/Type.h>
#include <vector>

namespace wasm_module {

    class FunctionType {
        const Type* returnType_ = nullptr;
        std::vector<const Type*> parameters_;
        bool variadic_ = true;

    public:
        FunctionType() {
        }
        FunctionType(const Type* returnType, const std::vector<const Type*>& parameters) : returnType_(returnType), parameters_(parameters), variadic_(false) {
        }
        FunctionType(const Type* returnType) : returnType_(returnType), variadic_(true) {
        }

        const std::vector<const Type*>& parameters() const {
            return parameters_;
        }

        const Type* returnType() const {
            return returnType_;
        }

        bool variadic() const {
            return variadic_;
        }

        bool compatibleWith(const FunctionType& other) const {
            if (returnType_ != other.returnType_)
                return false;

            if (variadic() || other.variadic())
                return true;

            if (parameters_.size() != other.parameters().size())
                return false;

            for (std::size_t i = 0; i < other.parameters().size(); i++) {
                if (parameters()[i] != other.parameters()[i]) {
                    return false;
                }
            }
            return true;
        }

        std::string toString() const;
    };

}


#endif //WASMINT_FUNCTIONTYPE_H

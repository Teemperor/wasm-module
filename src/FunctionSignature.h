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
#include <stdexcept>

#include "types/Type.h"
#include "Variable.h"

namespace wasm_module {

    /**
     * Contains all information that are relevant to an caller of the given function.
     */
    class FunctionSignature {

        std::string moduleName_;
        std::string name_;
        const Type* returnType_ = Void::instance();
        std::vector<const Type*> parameterTypes_;
        bool variadic_ = true;

    public:
        FunctionSignature() {
        }

        FunctionSignature(std::string module, std::string name, const Type* returnType,
                          std::vector<const Type*> parameterTypes)
                : moduleName_(module), name_(name), returnType_(returnType), parameterTypes_(parameterTypes),
                  variadic_(false) {
        }

        FunctionSignature(std::string module, std::string name, const Type* returnType)
                : moduleName_(module), name_(name), returnType_(returnType), variadic_(true) {
        }

        const Type* returnType() const {
            return returnType_;
        }

        const std::vector<const Type*>& parameters() const {
            return parameterTypes_;
        }

        const std::string& name() const {
            return name_;
        }

        const std::string& module() const {
            return moduleName_;
        }

        bool operator<(const FunctionSignature& other) const {
            if (name_ < other.name())
                return true;
            if (returnType_ < other.returnType_)
                return true;
            return false;
        }

        bool variadic() const {
            return variadic_;
        }

        FunctionSignature makeNonVariadic(std::vector<const Type*> parameterTypes) const {
            if (!variadic()) {
                throw std::domain_error("makeNonVariadic() can only be called on variadic functions. Current function is " + moduleName_ + "::" + name_);
            }

            FunctionSignature result(moduleName_, name_, returnType_, parameterTypes);

            return result;
        }
    };

}

#endif //WASMINT_FUNCTIONSIGNATURE_H

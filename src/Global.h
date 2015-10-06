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

#ifndef WASMINT_GLOBAL_H
#define WASMINT_GLOBAL_H

#include <string>
#include <types/Type.h>

namespace wasm_module {

    class Global {
        std::string name_;
        Type *type_;
    public:
        Global(std::string name, Type *type) : name_(name), type_(type) {

        }

        std::string name() {
            return name_;
        }

        Type *type() {
            return type_;
        }
    };

}

#endif //WASMINT_GLOBAL_H

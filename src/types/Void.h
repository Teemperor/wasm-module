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

#ifndef WASMINT_VOID_H
#define WASMINT_VOID_H


#include <types/Type.h>

namespace wasm_module {

    class NoVoidLiteralsSupported : public std::exception {
    };

    class Void : public Type {

    protected:
        Void() {
        }

    public:
        static Void *instance() {
            static Void instance;
            return &instance;
        }

        virtual std::string name() {
            return "void";
        }

        virtual void parse(ByteStream &stream, void *data) {
            throw NoVoidLiteralsSupported();
        }

        virtual std::size_t size() {
            return 1;
        }

    };

}

#endif //WASMINT_VOID_H

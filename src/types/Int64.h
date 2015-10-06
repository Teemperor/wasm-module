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

#ifndef WASMINT_INT64_H
#define WASMINT_INT64_H


#include <types/Type.h>
#include <Variable.h>

namespace wasm_module {

    class Int64 : public Type {

    protected:
        Int64() {
        }


    public:
        static Int64 *instance() {
            static Int64 instance;
            return &instance;
        }

        virtual std::string name() {
            return "int64";
        }

        virtual void parse(binary::ByteStream &stream, void *data) {
            int64_t value = stream.popULEB128() << 32; // FIXME
            value |= stream.popULEB128();
            (*(int64_t *) data) = value;
        }

        static int64_t getValue(Variable variable) {
            if (variable.type() == *instance()) {
                int64_t result = 0;
                int64_t *data = (int64_t *) variable.value();
                result = *data;
                return result;
            } else {
                throw IncompatibleType();
            }
        }

        static void setValue(Variable variable, int32_t value) {
            if (variable.type() == *instance()) {
                int32_t *data = (int32_t *) variable.value();
                (*data) = value;
            } else {
                throw IncompatibleType();
            }
        }

        virtual std::size_t size() {
            return 8;
        }

    };
}


#endif //WASMINT_INT64_H

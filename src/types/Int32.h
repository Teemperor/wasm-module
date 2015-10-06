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

#ifndef WASMINT_INT32_H
#define WASMINT_INT32_H


#include <types/Type.h>
#include <Variable.h>

namespace wasm_module {

    class Int32 : public Type {

    protected:
        Int32() {
        }


    public:
        static Int32 *instance() {
            static Int32 instance;
            return &instance;
        }

        virtual std::string name() {
            return "int32";
        }

        static int32_t getFromStream(binary::ByteStream &stream) {
            int32_t result = 0;
            uint32_t shift = 0;
            uint32_t size = 32;

            uint8_t byte;

            while (true) {
                byte = stream.popChar();


                result |= ((byte & 0x7F) << shift);
                shift += 7;

                if ((byte & 0x80u) == 0u)
                    break;
            }

            /* sign bit of byte is second high order bit (0x40) */
            if ((shift < size) && ((0x40 & byte) != 0))
                /* sign extend */
                result |= -(1 << shift);

            return result;
        }

        virtual void parse(binary::ByteStream &stream, void *data) {
            int32_t value = getFromStream(stream);
            (*(int32_t *) data) = value;
        }

        static int32_t getValue(Variable variable) {
            if (variable.type() == *instance()) {
                int32_t result = 0;
                int32_t *data = (int32_t *) variable.value();
                result = *data;
                return result;
            } else {
                throw IncompatibleType();
            }
        }

        static void setValue(Variable &variable, int32_t value) {
            if (variable.type() == *instance()) {
                int32_t *data = (int32_t *) variable.value();
                (*data) = value;
            } else {
                throw IncompatibleType();
            }
        }

        virtual std::size_t size() {
            return 4;
        }

    };

}

#endif //WASMINT_INT32_H

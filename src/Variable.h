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

#ifndef WASMINT_VARIABLE_H
#define WASMINT_VARIABLE_H

#include <cstdint>
#include <vector>
#include <types/Type.h>


namespace wasm_module {
    class Type;

    class InvalidDataSize : public std::exception {};

    class Variable {
        const wasm_module::Type *type_;
        std::vector<uint8_t> value_;

        void setType(const wasm_module::Type* type);

    public:
        Variable();
        Variable(uint32_t value);
        Variable(int32_t value);
        Variable(uint64_t value);
        Variable(int64_t value);
        Variable(float value);
        Variable(double value);

        static Variable Void();

        Variable(const wasm_module::Type *type);

        const wasm_module::Type& type() const {
            return *type_;
        }

        void* value() {
            return (void *) value_.data();
        }

        std::vector<uint8_t> data() {
            return value_;
        }

        void setValue(std::vector<uint8_t> newData);

        uint32_t uint32() const;

        int32_t int32() const;

        void uint32(uint32_t value);

        void int32(int32_t value);

        float float32() const;

        double float64() const;

        void float32(float value);

        void float64(double value);
    };
}


#endif //WASMINT_VARIABLE_H

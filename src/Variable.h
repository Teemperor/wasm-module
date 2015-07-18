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

class InvalidDataSize : public std::exception {};

class Type;

class Variable {
    Type* type_;
    std::vector<uint8_t> value_;

public:
    Variable();
    Variable(Type* type);

    Type& type() {
        return *type_;
    }

    void* value() {
        return (void*) value_.data();
    }

    std::vector<uint8_t> data() {
        return value_;
    }

    void setValue(std::vector<uint8_t> newData);
};


#endif //WASMINT_VARIABLE_H

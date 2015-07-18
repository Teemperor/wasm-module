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

#ifndef WASMINT_TYPE_H
#define WASMINT_TYPE_H


#include <cstdint>
#include <parsing/ByteStream.h>
#include <typeinfo>
#include <Variable.h>

class IncompatibleType : public std::exception {};

class Type {

protected:
    Type() {

    }

public:
    Type(const Type& type) {

    }

    virtual Type* localType() {
        return this;
    }

    virtual std::vector<uint8_t> convertFromMemoryType(std::vector<uint8_t> bytes, Type* memoryType) {
        return bytes;
    }

    virtual std::string name() = 0;

    virtual void parse(ByteStream& stream, void* data) = 0;

    virtual std::size_t size() = 0;

    bool operator==(const Type& other) const {
        return typeid(*this) == typeid(other);
    }

    bool operator!=(const Type& other) const {
        return typeid(*this) != typeid(other);
    }

};


#endif //WASMINT_TYPE_H

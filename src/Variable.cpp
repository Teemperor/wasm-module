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

#include <types/Void.h>
#include <types/Int32.h>
#include "Variable.h"
#include "types/Type.h"


namespace wasm_module {

    Variable::Variable(const wasm_module::Type *type) {
        setType(type);
    }

    Variable::Variable() : type_(wasm_module::Void::instance()) {
    }

    void Variable::setValue(std::vector<uint8_t> newData) {
        if (newData.size() != type_->size())
            throw InvalidDataSize();
        value_ = newData;
    }

    uint32_t Variable::uint32() const {
        if (type_ != Int32::instance())
            throw InvalidTypeForShortMethod();
        return Int32::getUnsignedValue(*this);
    }

    int32_t Variable::int32() const {
        if (type_ != Int32::instance())
            throw InvalidTypeForShortMethod();
        return Int32::getValue(*this);
    }

    Variable::Variable(uint32_t value) {
        setType(Int32::instance());
        uint32(value);
    }

    Variable::Variable(int32_t value) {
        setType(Int32::instance());
        int32(value);
    }

    void Variable::setType(const wasm_module::Type* type) {
        type_ = type;
        value_.resize(type->size());
    }

    void Variable::uint32(uint32_t value) {
        if (type_ != Int32::instance())
            throw InvalidTypeForShortMethod();
        Int32::setUnsignedValue(*this, value);
    }

    void Variable::int32(int32_t value) {
        if (type_ != Int32::instance())
            throw InvalidTypeForShortMethod();
        Int32::setValue(*this, value);
    }
}
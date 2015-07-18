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
#include "Variable.h"
#include "types/Type.h"

Variable::Variable(Type* type) : type_(type) {
    value_.resize(type->size());
}

Variable::Variable() : type_(Void::instance()) {
}

void Variable::setValue(std::vector<uint8_t> newData) {
    if (newData.size() != type_->size())
        throw InvalidDataSize();
    value_ = newData;
}
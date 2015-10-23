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



#include "Int64.h"
namespace wasm_module {

    const std::regex Int64::hexNumber("0(x|X)[0-9a-fA-F]{1,16}");
    const std::regex Int64::decNumber("(-|\\+)?[0-9]+");

    void Int64::parse(const std::string& literal, void *data) const {
        uint64_t value = 0;
        if (std::regex_match(literal, hexNumber)) {
            for(std::size_t i = 2; i < literal.size(); i++) {
                char c = literal[i];
                if (c >= 'a' && c <= 'f') {
                    value |= c - 'a';
                } else if (c >= 'A' && c <= 'F') {
                    value |= c - 'A';
                } else {
                    value |= c - '0';
                }
                value <<= 4u;
            }
        } else if (std::regex_match(literal, decNumber)) {
            for(std::size_t i = 2; i < literal.size(); i++) {
                char c = literal[i];
                value += c - '0';
                value *= 10;
            }
        } else {
            throw InvalidI64Format(literal);
        };

        (*(int64_t*) data) = value;
    }
}

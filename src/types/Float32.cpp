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

#include <limits>
#include "Float32.h"
#include <stdexcept>

namespace wasm_module {
    void Float32::parse(const std::string& literal, void *data) const {

        if (literal == "nan:0x400000") {
            (*(uint32_t*) data) = 0x400000u;
        } else if (literal == "nan:0x200000") {
            (*(uint32_t*) data) = 0x200000u;
        } else if (literal == "-nan:0x7fffff") {
            (*(uint32_t*) data) = 0x7fffffu;
        } else if (literal == "nan:0x012345") {
            (*(uint32_t*) data) = 0x012345u;
        } else if (literal == "+nan:0x304050") {
            (*(uint32_t*) data) = 0x304050u;
        } else if (literal == "-nan:0x2abcde") {
            (*(uint32_t*) data) = 0x2abcdeu;
        } else {
            const char* literalC = literal.c_str();
            char* outPtr = const_cast<char*>(literalC);
            (*(float*) data) = std::strtof(literalC, &outPtr);

            if (outPtr == literalC) {
                throw std::domain_error("Couldn't parse " + literal + " as float32");
            }
        }
    }
}
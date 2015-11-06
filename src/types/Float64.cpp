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
#include "Float64.h"

namespace wasm_module {

    void Float64::parse(const std::string& literal, void *data) const {
        if (literal == "-nan") {
            double value = -std::numeric_limits<double>::quiet_NaN();
            (*(double*) data) = value;
            return;
        }
        (*(double*) data) = std::atof(literal.c_str());
    }
}
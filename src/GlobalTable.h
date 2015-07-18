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

#ifndef WASMINT_GLOBALTABLE_H
#define WASMINT_GLOBALTABLE_H

#include <vector>
#include "Global.h"

#include "ExceptionWithMessage.h"

ExceptionMessage(NoGlobalWithIndex)

class GlobalTable {

    std::vector<Global> globals;
    std::vector<Global> internalGlobals_;

public:
    void addGlobal(Global global, bool internal) {
        globals.push_back(global);
        if (internal)
            internalGlobals_.push_back(global);
    }

    Global& getGlobal(uint32_t globalIndex) {
        if (globalIndex >= globals.size())
            throw NoGlobalWithIndex(std::to_string(globalIndex));

        return globals[globalIndex];
    }

    std::vector<Global> internalGlobals() {
        return internalGlobals_;
    }

};


#endif //WASMINT_GLOBALTABLE_H

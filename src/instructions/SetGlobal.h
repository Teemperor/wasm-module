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
 *///
// Created by teemperor on 21.06.15.
//

#ifndef WASMINT_SETGLOBAL_H
#define WASMINT_SETGLOBAL_H


#include <ModuleContext.h>
#include "Instruction.h"

class SetGlobal : public Instruction {

    Type* expectedType;

public:
    std::string globalName;
    SetGlobal(ByteStream& stream, ModuleContext& context) {
        uint32_t globalIndex = stream.popULEB128();
        expectedType = context.globalTable().getGlobal(globalIndex).type();
        globalName = context.globalTable().getGlobal(globalIndex).name();
    }

    virtual std::string name() {
        return "set_global";
    }

    virtual std::vector<Type*> childrenTypes() {
        return {expectedType};
    }

    virtual Type* returnType() {
        return expectedType;
    }
};



#endif //WASMINT_SETGLOBAL_H

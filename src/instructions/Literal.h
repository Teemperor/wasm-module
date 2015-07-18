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

#ifndef WASMINT_LITERAL_H
#define WASMINT_LITERAL_H


#include <ModuleContext.h>
#include "Instruction.h"

class Literal : public Instruction {
    Variable literalValue;

public:
    Literal(ByteStream& stream, ModuleContext& context) {
        uint32_t typeId = stream.popULEB128();

        Type* type = context.typeTable().getType(typeId);

        literalValue = Variable(type);
        type->parse(stream, literalValue.value());
    }

    virtual std::vector<Type*> childrenTypes() {
        return {};
    }

    virtual std::string name() {
        return "literal";
    }

    virtual Type* returnType() {
        return &literalValue.type();
    }
};


#endif //WASMINT_LITERAL_H

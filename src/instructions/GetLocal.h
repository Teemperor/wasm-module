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

#ifndef WASMINT_GETLOCAL_H
#define WASMINT_GETLOCAL_H


#include <instructions/Instruction.h>
#include <parsing/ByteStream.h>
#include <FunctionContext.h>

class GetLocal : public Instruction {

    Type* returnType_;

public:
    uint32_t localIndex;

    GetLocal(ByteStream& stream, FunctionContext& context) {
        localIndex = stream.popULEB128();
        returnType_ = context.pureLocals().at(localIndex);
    }

    virtual std::string name() {
        return "get_local";
    }

    virtual std::vector<Type*> childrenTypes() {
        return {};
    }

    virtual Type* returnType() {
        return returnType_;
    }
};


#endif //WASMINT_GETLOCAL_H

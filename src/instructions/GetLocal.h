//
// Created by teemperor on 19.06.15.
//

#ifndef WASMINT_GETLOCAL_H
#define WASMINT_GETLOCAL_H


#include <Instruction.h>
#include <parsing/ByteStream.h>

class GetLocal : public Instruction {

    uint32_t localIndex;

public:
    GetLocal(ByteStream& stream) {
        localIndex = stream.popLEB128();
    }

    virtual std::vector<Type*> childrenTypes() {
        return {};
    }

    virtual Type* returnType() {
        return Void::instance();
    }

    virtual Variable execute(Environment& env) {
        return env.variable(localIndex);
    }
};


#endif //WASMINT_GETLOCAL_H
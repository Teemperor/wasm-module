

#ifndef WASMINT_I32ADD_H
#define WASMINT_I32ADD_H


#include <types/Int32.h>
#include <assert.h>
#include "instructions/Instruction.h"

class I32Add : public Instruction {

public:
    virtual std::vector<Type*> childrenTypes() {
        return {Int32::instance(), Int32::instance()};
    }

    virtual std::string name() {
        return "int32.add";
    }


    virtual Type* returnType() {
        return Int32::instance();
    }
};


#endif //WASMINT_I32ADD_H

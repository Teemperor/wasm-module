

#ifndef WASMINT_I32DIV_H
#define WASMINT_I32DIV_H

#include <exception>
#include <instructions/Instruction.h>
#include <types/Int32.h>

class DivisionThroughZero : std::exception {};

class I32Div : public Instruction {

public:
    virtual std::vector<Type*> childrenTypes() {
        return {Int32::instance(), Int32::instance()};
    }

    virtual std::string name() {
        return "int32.div";
    }


    virtual Type* returnType() {
        return Int32::instance();
    }
};


#endif //WASMINT_I32DIV_H



#ifndef WASMINT_PRINT_H
#define WASMINT_PRINT_H

#include <instructions/Instruction.h>
#include <iostream>
#include <types/Int32.h>
#include <types/Void.h>

class Print : public Instruction {
public:
    virtual std::vector<Type*> childrenTypes() {
        return {Int32::instance()};
    }

    virtual std::string name() {
        return "print";
    }

    virtual Type* returnType() {
        return Void::instance();
    }
};


#endif //WASMINT_PRINT_H

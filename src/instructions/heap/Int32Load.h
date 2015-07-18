

#ifndef WASMINT_LOADHEAP_H
#define WASMINT_LOADHEAP_H


#include <instructions/Instruction.h>
#include <types/Int32.h>

class Int32Load : public Instruction {

public:
    virtual std::vector<Type*> childrenTypes() {
        return {Int32::instance()};
    }

    virtual Type* returnType() {
        return Int32::instance();
    }

    virtual std::string name() {
        return "int32.load";
    }
};


#endif //WASMINT_LOADHEAP_H

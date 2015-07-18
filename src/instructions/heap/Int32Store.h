

#ifndef WASMINT_STOREHEAP_H
#define WASMINT_STOREHEAP_H


#include <instructions/Instruction.h>
#include <types/Int32.h>

class Int32Store : public Instruction {

public:
    virtual std::vector<Type*> childrenTypes() {
        return {Int32::instance(), Int32::instance()};
    }

    virtual Type* returnType() {
        return Int32::instance();
    }

    virtual std::string name() {
        return "int32.store";
    }
};


#endif //WASMINt_STOREHEAP_H

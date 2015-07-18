

#ifndef WASMINT_RETURN_H
#define WASMINT_RETURN_H


#include <instructions/Instruction.h>
#include <types/Int32.h>
#include <types/Void.h>

class CalledReturn {
public:
    Variable result;
};

class Return : public Instruction {
public:
    virtual std::vector<Type*> childrenTypes() {
        return {Int32::instance()};
    }

    virtual std::string name() {
        return "return";
    }

    virtual Type* returnType() {
        return Void::instance();
    }
};



#endif //WASMINT_RETURN_H

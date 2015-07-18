

#ifndef WASMINT_CONTINUE_H
#define WASMINT_CONTINUE_H


#include <instructions/Instruction.h>
#include <types/Void.h>

class CalledContinue {};

class Continue : public Instruction {
public:
    virtual std::vector<Type*> childrenTypes() {
        return {};
    }
    virtual std::string name() {
        return "continue";
    }

    virtual Type* returnType() {
        return Void::instance();
    }
};



#endif //WASMINT_CONTINUE_H

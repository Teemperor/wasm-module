

#ifndef WASMINT_IF_H
#define WASMINT_IF_H


#include <instructions/Instruction.h>
#include <types/Int32.h>
#include <types/Void.h>

class If : public Instruction {
public:
    virtual std::vector<Type*> childrenTypes() {
        return {Int32::instance(), Void::instance()};
    }

    virtual std::string name() {
        return "if";
    }

    virtual Type* returnType() {
        return Void::instance();
    }
};



#endif //WASMINT_IF_H

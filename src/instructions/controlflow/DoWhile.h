

#ifndef WASMINT_DOWHILE_H
#define WASMINT_DOWHILE_H


#include <instructions/Instruction.h>
#include <types/Int32.h>
#include <types/Void.h>
#include "Break.h"
#include "Continue.h"

class DoWhile : public Instruction {
public:
    virtual std::vector<Type*> childrenTypes() {
        return {Void::instance(), Int32::instance()};
    }

    virtual std::string name() {
        return "do_while";
    }

    virtual Type* returnType() {
        return Void::instance();
    }
};



#endif //WASMINT_DOWHILE_H

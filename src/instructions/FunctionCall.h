

#ifndef WASMINT_FUNCTIONCALL_H
#define WASMINT_FUNCTIONCALL_H


#include <instructions/Instruction.h>
#include <ModuleContext.h>

class FunctionCall : public Instruction {

    FunctionSignature functionSignature;

public:
    FunctionCall(ByteStream& stream, ModuleContext& context) {
        functionSignature = context.functionTable().getFunctionSignature(stream.popULEB128());
    }

    virtual std::string name() {
        return "call_direct";
    }

    virtual std::vector<Type*> childrenTypes() {
        return functionSignature.parameters();
    }

    virtual Type* returnType() {
        return functionSignature.returnType();
    }
};


#endif //WASMINT_FUNCTIONCALL_H

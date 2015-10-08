#ifndef WASMINT_NATIVEINSTRUCTION_H
#define WASMINT_NATIVEINSTRUCTION_H

#include <functional>
#include "Instruction.h"

namespace wasm_module {
    class NativeInstruction : public Instruction {

        std::function<Variable(std::vector<Variable>)> internalFunction_;
        std::vector<Type*> parameterTypes_;
        Type* returnType_;

    public:
        NativeInstruction(std::function<Variable(std::vector<Variable>)> internalFunction, Type* returnType, std::vector<Type*> parameterTypes)
                : internalFunction_(internalFunction), parameterTypes_(parameterTypes)
        {
        }

        virtual std::vector<Type *> childrenTypes() {
            return parameterTypes_;
        }

        virtual std::string name() {
            return "native";
        }

        virtual Type *returnType() {
            return returnType_;
        }

        Variable call(std::vector<Variable> parameters) {
            return internalFunction_(parameters);
        }
    };
}

#endif //WASMINT_NATIVEINSTRUCTION_H

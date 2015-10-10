#ifndef WASMINT_NATIVEINSTRUCTION_H
#define WASMINT_NATIVEINSTRUCTION_H

#include <functional>
#include "Instruction.h"

namespace wasm_module {
    class NativeInstruction : public Instruction {

        std::function<Variable(std::vector<Variable>)> internalFunction_;
        std::vector<const Type*> parameterTypes_;
        const Type* returnType_;

    public:
        NativeInstruction(std::function<Variable(std::vector<Variable>)> internalFunction, const Type* returnType, std::vector<const Type*> parameterTypes)
                : internalFunction_(internalFunction), parameterTypes_(parameterTypes)
        {
        }

        virtual std::vector<const Type*> childrenTypes() override {
            return parameterTypes_;
        }

        virtual std::string name() {
            return "native";
        }

        virtual const Type* returnType() override {
            return returnType_;
        }

        Variable call(std::vector<Variable> parameters) {
            return internalFunction_(parameters);
        }
    };
}

#endif //WASMINT_NATIVEINSTRUCTION_H

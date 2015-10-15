#ifndef WASMINT_ASSERTRETURN_H
#define WASMINT_ASSERTRETURN_H

#include <instructions/Instruction.h>
#include <types/Int64.h>
#include <types/Void.h>

namespace wasm_module {

    class I32AssertReturn : public Instruction {

    public:
        virtual const std::vector<const Type*>& childrenTypes() const override {
            static std::vector<const Type*> chTypes_ = {Int64::instance(), Int64::instance()};;
            return chTypes_;
        }

        virtual const std::string& name() const override {
            static std::string name_ = "print";
            return name_;
        }

        virtual const Type* returnType() const override {
            return Void::instance();
        }

        virtual InstructionId::Value id() const override {
            return InstructionId::I32AssertReturn;
        }
    };
}


#endif //WASMINT_ASSERTRETURN_H

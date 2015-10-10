#ifndef WASMINT_ASSERTRETURN_H
#define WASMINT_ASSERTRETURN_H

#include <instructions/Instruction.h>
#include <types/Int64.h>
#include <types/Void.h>

namespace wasm_module {

    class I32AssertReturn : public Instruction {

    public:
        virtual std::vector<const Type*> childrenTypes() override {
            return {Int64::instance(), Int64::instance()};
        }

        virtual std::string name() {
            return "int32.assert_return";
        }

        virtual const Type* returnType() override {
            return Void::instance();
        }
    };
}


#endif //WASMINT_ASSERTRETURN_H

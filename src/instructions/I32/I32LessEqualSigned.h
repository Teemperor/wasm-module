//
// Created by teemperor on 12.10.15.
//

#ifndef WASMINT_I32LESSEQUAL_H
#define WASMINT_I32LESSEQUAL_H


#include <instructions/Instruction.h>
#include <types/Int32.h>

namespace wasm_module {

    class I32LessEqualSigned : public Instruction {

    public:
        virtual std::vector<const Type*> childrenTypes() override {
            return {Int32::instance(), Int32::instance()};
        }

        virtual std::string name() {
            return "i32.le";
        }


        virtual const Type* returnType() override {
            return Int32::instance();
        }
    };
}

#endif //WASMINT_I32LESSEQUAL_H

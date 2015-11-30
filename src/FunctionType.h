//
// Created by teemperor on 30.11.15.
//

#ifndef WASMINT_FUNCTIONTYPE_H
#define WASMINT_FUNCTIONTYPE_H

#include <types/Type.h>
#include <vector>

namespace wasm_module {

    class FunctionType {
        const Type* returnType_ = nullptr;
        std::vector<const Type*> parameters_;
        bool variadic_ = true;

    public:
        FunctionType() {
        }
        FunctionType(const Type* returnType, const std::vector<const Type*>& parameters) : returnType_(returnType), parameters_(parameters), variadic_(false) {
        }
        FunctionType(const Type* returnType) : returnType_(returnType), variadic_(true) {
        }

        const std::vector<const Type*>& parameters() const {
            return parameters_;
        }

        const Type* returnType() const {
            return returnType_;
        }

        bool variadic() const {
            return variadic_;
        }

        bool compatibleWith(const FunctionType& other) const {
            if (returnType_ != other.returnType_)
                return false;

            if (variadic() || other.variadic())
                return true;

            if (parameters_.size() != other.parameters().size())
                return false;

            for (std::size_t i = 0; i < other.parameters().size(); i++) {
                if (parameters()[i] != other.parameters()[i]) {
                    return false;
                }
            }
            return true;
        }

    };

}


#endif //WASMINT_FUNCTIONTYPE_H

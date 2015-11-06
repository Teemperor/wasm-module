/*
 * Copyright 2015 WebAssembly Community Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WASMINT_OPCODE_H
#define WASMINT_OPCODE_H


#include <cstdint>
#include <vector>
#include <ExceptionWithMessage.h>

#include "types/Type.h"
#include "Variable.h"
#include "InstructionId.h"

namespace wasm_module {

    ExceptionMessage(IncompatibleChildReturnType)
    ExceptionMessage(IncompatibleNumberOfChildren)

    class InstructionState;

    class Instruction {

        std::vector<Instruction *> children_;

    public:
        virtual ~Instruction() {
            for (Instruction *child : children()) {
                delete child;
            }
        }

        virtual void children(const std::vector<Instruction*>& newChildren) {
            if (typeCheckChildren()) {
                if (newChildren.size() != childrenTypes().size()) {
                    throw IncompatibleNumberOfChildren(name() + " got " + std::to_string(newChildren.size()) + " children, but expected " +  std::to_string(childrenTypes().size()));
                }

                for (std::size_t i = 0; i < newChildren.size(); i++) {
                    if (!Type::typeCompatible(childrenTypes()[i], newChildren[i]->returnType())) {
                        throw IncompatibleChildReturnType(name() + " expected " + childrenTypes()[i]->name() + " but got " + newChildren[i]->returnType()->name());
                    }
                }
            }
            children_ = newChildren;
        }

        const std::vector<Instruction *>& children() const {
            return children_;
        }

        virtual bool typeCheckChildren() const {
            return true;
        }

        virtual const std::string& name() const = 0;

        virtual const std::vector<const Type *>& childrenTypes() const = 0;

        virtual const Type* returnType() const = 0;

        virtual InstructionId::Value id() const = 0;

        virtual std::string dataString() const {
            return name();
        }

        virtual std::string toSExprString() const {
            std::string result = "(";

            result += dataString();
            if (!children_.empty())
                result += " ";

            for (std::size_t i = 0; i < children_.size(); i++) {
                result += children_[i]->toSExprString();
                if (i != children_.size() - 1)
                    result += " ";
            }

            result += ")";

            return result;
        }

    };
}

#endif //WASMINT_OPCODE_H

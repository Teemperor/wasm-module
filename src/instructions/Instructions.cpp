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

#include <sexpr_parsing/Types.h>
#include "Instructions.h"


namespace wasm_module {

    Literal::Literal(const sexpr::SExpr& expr) {
        std::string value = expr[1].value();
        std::string typeName = expr[0].value().substr(0, 3);

        literalValueStr_ = value;

        const Type* type = sexpr::Types::getByName(typeName);
        literalValue_ = Variable(type);
        type->parse(value, literalValue_.value());
    }

    LoadStoreInstruction::LoadStoreInstruction(const wasm_module::sexpr::SExpr& expr) {
        for (const sexpr::SExpr& child : expr.children()) {
            if (child.hasValue()) {
                if(child.value().find("offset=") == 0) {
                    std::string value = child.value().substr(std::string("offset=").size());
                    offset_ = (uint32_t) std::atol(value.c_str());
                }
            }
        }
    }

    void Loop::secondStepEvaluate(ModuleContext& context, FunctionContext& functionContext) {
        if (!children().empty()) {
            returnType_ = children().back()->returnType();
        }
    }

    void Block::secondStepEvaluate(ModuleContext& context, FunctionContext& functionContext) {
        if (!children().empty()) {
            returnType_ = children().back()->returnType();
        }
    }

    void BranchIf::secondStepEvaluate(ModuleContext& context, FunctionContext& functionContext) {
        if (!labelName_.empty()) {
            bool foundTarget = false;
            foreachParent([&](const Instruction *instruction) {
                if (instruction->hasLabelName(labelName_)) {
                    branchLabel_ += instruction->labelIndex(labelName_);
                    foundTarget = true;
                    return false;
                } else {
                    branchLabel_ += instruction->labelCount();
                    return true;
                }
            });
            if (!foundTarget) {
                throw CantFindBranchTarget("Can't find branch target: " + labelName_);
            }
        }
    }

    void Branch::secondStepEvaluate(ModuleContext& context, FunctionContext& functionContext) {
        if (!labelName_.empty()) {
            bool foundTarget = false;
            foreachParent([&](const Instruction *instruction) {
                if (instruction->hasLabelName(labelName_)) {
                    branchLabel_ += instruction->labelIndex(labelName_);
                    foundTarget = true;
                    return false;
                } else {
                    branchLabel_ += instruction->labelCount();
                    return true;
                }
            });
            if (!foundTarget) {
                throw CantFindBranchTarget("Can't find branch target: " + labelName_);
            }
        }
    }
}
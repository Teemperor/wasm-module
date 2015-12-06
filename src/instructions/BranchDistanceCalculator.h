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


#ifndef WASMINT_BRANCHDISTANCECALCULATOR_H
#define WASMINT_BRANCHDISTANCECALCULATOR_H

#include <cstdint>
#include "Instruction.h"
#include <string>
#include <branching/BranchInformation.h>

namespace wasm_module {
    ExceptionMessage(CantFindBranchTarget);

    class BranchDistanceCalculator {
    public:
        static BranchInformation getBranchInformation(const Instruction& start, std::string& labelName, const Type* valueType) {
            uint32_t labelIndex = 0;
            uint32_t label = 0;
            const Instruction* target = nullptr;

            if (!labelName.empty()) {
                bool foundTarget = false;
                start.foreachParent([&](const Instruction* instruction) {
                    if (instruction->hasLabelName(labelName)) {
                        target = instruction;
                        label += instruction->labelIndex(labelName);
                        labelIndex = instruction->labelIndex(labelName);
                        foundTarget = true;
                        return false;
                    } else {
                        label += instruction->labelCount();
                        return true;
                    }
                });
                if (!foundTarget) {
                    throw CantFindBranchTarget("Can't find branch target: " + labelName);
                }
            } else {
                throw std::domain_error("labelName can't be empty");
            }
            return BranchInformation(labelIndex, target, label, valueType);
        }

        static const Instruction& getBranchTarget(const Instruction& start, std::size_t distance) {

        }
    };
}

#endif //WASMINT_BRANCHDISTANCECALCULATOR_H

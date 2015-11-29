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

#include "ModuleParser.h"
#include "FunctionParser.h"


namespace wasm_module { namespace sexpr {


        ModuleParser::ModuleParser(const SExpr& moduleExpr) {
            for(unsigned i = 1; i < moduleExpr.children().size(); i++) {
                const SExpr& expr = moduleExpr[i];
                const std::string& typeName = expr[0].value();
                if (typeName == "import") {
                    parseImport(expr);
                } else if (typeName == "memory") {
                    parseMemory(expr);
                } else if (typeName == "func") {
                    Function* function = &FunctionParser::parse(expr, module_->context());
                    module_->context().mainFunctionTable().addFunctionSignature(*function, function->name());
                    module_->addFunction(function, true);
                } else {
                    throw UnknownModuleChild(typeName);
                }
            }
            for (Function* function : module_->functions()) {
                function->mainInstruction()->triggerSecondStepEvaluate(module_->context(), *function);
            }
        }

        void ModuleParser::parseImport(const SExpr& importExpr) {
            if (importExpr.children().size() < 4) {
                throw MalformedImportStatement(importExpr.toString());
            } else {
                if (importExpr[0] != "import") {
                    throw MalformedImportStatement(importExpr.toString());
                }

                std::string importName = importExpr[1].value();
                std::string moduleName = importExpr[2].value();
                std::string functionName = importExpr[3].value();

                const Type* returnType = Void::instance();

                std::vector<const Type*> parameters;

                for (uint32_t i = 4; i < importExpr.children().size(); i++) {
                    const SExpr& subExpr = importExpr[i];

                    if (subExpr[0].value() == "param") {
                        for (std::size_t i = 1; i < subExpr.children().size(); i++)
                            parameters.push_back(Types::getByName(subExpr[i].value()));
                    } else if (subExpr[0].value() == "return") {
                        if (returnType != Void::instance()) {
                            throw MultipleReturnTypesInImport(importExpr.toString());
                        }

                        returnType = Types::getByName(subExpr[1].value());
                    } else {
                        throw UnknownImportExpressionChild(subExpr.value());
                    }
                }

                module_->importedFunctionTable().addFunctionSignature(FunctionSignature(moduleName, functionName, returnType, parameters), importName);
            }
        }

        void ModuleParser::parseMemory(const SExpr&memoryExpr) {
            if (memoryExpr.children().size() >= 2) {
                uint32_t startMem = (uint32_t) std::atoll(memoryExpr[1].value().c_str());
                uint32_t maxMem = std::numeric_limits<uint32_t>::max();
                bool hasMaxValue = false;

                if (memoryExpr.children().size() >= 3) {
                    hasMaxValue = memoryExpr[2].hasValue();
                }

                if (hasMaxValue) {
                    maxMem = (uint32_t) std::atoll(memoryExpr[2].value().c_str());
                }
                HeapData data(startMem, maxMem);

                for(uint32_t childNum = hasMaxValue ? 3 : 2; childNum < memoryExpr.children().size(); childNum++) {
                    const SExpr& segmentExpr = memoryExpr[childNum];
                    if (segmentExpr.children().size() >= 3) {
                        uint32_t offset = (uint32_t) std::atoll(segmentExpr[1].value().c_str());
                        // todo char to uint8_t is maybe compiler specific
                        std::vector<uint8_t> segmentData(segmentExpr[2].value().begin(), segmentExpr[2].value().end());

                        HeapSegment segment(offset, segmentData);
                        data.addNextSegment(segment);
                    } else {
                        throw MalformedMemoryStatement("Not enough children for a valid segment statement (needs at least 3): " + segmentExpr.toString());
                    }
                }

                module_->heapData(data);
            } else {
                throw MalformedMemoryStatement("Not enough children for a valid memory statement (needs at least 3): " + memoryExpr.toString());
            }
        }
    }}
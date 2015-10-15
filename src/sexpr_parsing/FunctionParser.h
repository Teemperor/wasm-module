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


#ifndef WASMINT_FUNCTIONPARSER_H
#define WASMINT_FUNCTIONPARSER_H

#include <Function.h>
#include <ExceptionWithMessage.h>
#include "SExpr.h"
#include "Types.h"
#include "InstructionParser.h"
#include <unordered_map>

namespace wasm_module { namespace sexpr {

    ExceptionMessage(UnexpectedTokenInFunction);
    ExceptionMessage(MissingFunctionName);
    ExceptionMessage(MalformedLocalStatement);
    ExceptionMessage(MalformedParamStatement);
    ExceptionMessage(MalformedResultStatement);
    ExceptionMessage(MultipleReturnTypes);
    ExceptionMessage(VariableDeclarationAfterFunctionBody);

    class FunctionParser {

        ModuleContext& context_;

        std::vector<const Type*> locals;
        std::vector<const Type*> parameters;

        std::unordered_map<std::string, uint32_t> namesToIndex_;

        FunctionContext functionContext_;

        Function* function_;

        const Type* returnType = Void::instance();

        std::string functionName_;

        Instruction* instruction_ = nullptr;

        void parseLocal(const SExpr& local) {
            if (local.children().size() == 3) {
                std::string variableName = local[1].value();
                std::string typeName = local[2].value();

                const Type* type = Types::getByName(typeName);

                namesToIndex_[variableName] = parameters.size() + locals.size();
                locals.push_back(type);
            } else {
                throw MalformedLocalStatement(local.toString());
            }
        }

        void parseParam(const SExpr& param) {
            if (param.children().size() == 1) {
                // empty parameter
            }
            else if (param.children().size() == 3) {
                std::string paramName = param[1].value();
                std::string typeName = param[2].value();
                const Type* type = Types::getByName(typeName);

                namesToIndex_[paramName] = parameters.size();
                parameters.push_back(type);
            } else {
                throw MalformedLocalStatement(param.toString());
            }
        }

        void parseResult(const SExpr& result) {

            if (result.children().size() == 2) {
                std::string resultTypeName = result[1].value();
                const Type* newReturnType = Types::getByName(resultTypeName);

                if (returnType != Void::instance()) {
                    throw MultipleReturnTypes(std::string("Return type was already defines as ") + returnType->name()
                                              + std::string(", can't assign new return type ")
                                              + newReturnType->name());
                }
                returnType = newReturnType;
            } else {
                throw MalformedResultStatement(result.toString());
            }
        }

        void parseInstructions(std::vector<const SExpr*>& instructionExprs) {
            if (instructionExprs.size() == 1) {
                instruction_ = InstructionParser::parse(*instructionExprs.front(), context_, functionContext_);
            } else {

                instruction_ = new Block((uint32_t) instructionExprs.size());
                std::vector<Instruction*> children;
                for (const SExpr* expr : instructionExprs) {
                    Instruction* newInstruction = InstructionParser::parse(*expr, context_, functionContext_);
                    children.push_back(newInstruction);
                }
                instruction_->children(children);

            }
        }

        FunctionParser(const SExpr& funcExpr, ModuleContext& context) : context_(context) {
            if (funcExpr.children().size() < 2) {
                throw MissingFunctionName(funcExpr.toString());
            }
            functionName_ = funcExpr[1].value();

            for(unsigned i = 2; i < funcExpr.children().size(); i++) {
                const SExpr& expr = funcExpr[i];

                if (expr.hasValue()) {
                    throw UnexpectedTokenInFunction(std::string("Got '") + expr.value() + "' in Expression: " + expr.value());
                }

                const std::string& typeName = expr[0].value();

                if (typeName == "param") {
                    parseParam(expr);
                }
            }
            for(unsigned i = 2; i < funcExpr.children().size(); i++) {
                const SExpr& expr = funcExpr[i];

                if (expr.hasValue()) {
                    throw UnexpectedTokenInFunction(std::string("Got '") + expr.value() + "' in Expression: " + expr.value());
                }

                const std::string& typeName = expr[0].value();

                if (typeName == "local") {
                    parseLocal(expr);
                }
            }
            for(unsigned i = 2; i < funcExpr.children().size(); i++) {
                const SExpr& expr = funcExpr[i];

                if (expr.hasValue()) {
                    throw UnexpectedTokenInFunction(std::string("Got '") + expr.value() + "' in Expression: " + expr.value());
                }

                const std::string& typeName = expr[0].value();

                if (typeName == "result") {
                    parseResult(expr);
                }
            }

            functionContext_ = FunctionContext(functionName_, returnType, parameters, locals, false);
            functionContext_.setVariableNameToIndexMap(namesToIndex_);

            std::vector<const SExpr*> instructionExprs;
            for(unsigned i = 2; i < funcExpr.children().size(); i++) {
                const SExpr& expr = funcExpr[i];

                if (expr.hasValue()) {
                    throw UnexpectedTokenInFunction(std::string("Got '") + expr.value() + "' in Expression: " + expr.value());
                }

                const std::string& typeName = expr[0].value();

                if (typeName != "local" && typeName != "param" && typeName != "result") {
                    instructionExprs.push_back(&expr);
                }
            }
            parseInstructions(instructionExprs);
            function_ = new Function(functionContext_, instruction_);
        }

        Function& getParsedFunction() {
            return *function_;
        }


    public:
        static Function& parse(const SExpr& funcExpr, ModuleContext& context) {
            FunctionParser parser(funcExpr, context);
            return parser.getParsedFunction();
        }
    };

}}


#endif //WASMINT_FUNCTIONPARSER_H

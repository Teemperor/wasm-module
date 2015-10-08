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



#include "InstructionSet.h"
#include "Literal.h"
#include "SetGlobal.h"
#include "GetGlobal.h"
#include <instructions/I32/I32Add.h>
#include <instructions/Print.h>
#include <instructions/GetLocal.h>
#include <instructions/controlflow/Block.h>
#include <instructions/SetLocal.h>
#include <instructions/controlflow/Break.h>
#include <instructions/controlflow/Continue.h>
#include <instructions/controlflow/DoWhile.h>
#include <instructions/controlflow/If.h>
#include <instructions/controlflow/Return.h>
#include <instructions/controlflow/Forever.h>
#include <instructions/FunctionCall.h>
#include <instructions/I32/I32Sub.h>
#include <instructions/I32/I32Mul.h>
#include <instructions/I32/I32Div.h>
#include <instructions/heap/Int32Load.h>
#include <instructions/heap/Int32Store.h>

namespace wasm_module {

    Instruction *InstructionSet::getInstruction(std::string name, binary::ByteStream &stream, ModuleContext &context,
                                                FunctionContext &functionContext) {
        if (name == "literal") {
            return new Literal(stream, context);
        } else if (name == "int32.add") {
            return new I32Add();
        } else if (name == "int32.sub") {
            return new I32Sub();
        } else if (name == "int32.mul") {
            return new I32Mul();
        } else if (name == "int32.div") {
            return new I32Div();
        } else if (name == "print") {
            return new Print();
        } else if (name == "call_direct") {
            return new FunctionCall(stream, context);
        } else if (name == "get_local") {
            return new GetLocal(stream, functionContext);
        } else if (name == "block") {
            return new Block(stream);
        } else if (name == "set_local") {
            return new SetLocal(stream, functionContext);
        } else if (name == "break") {
            return new Break();
        } else if (name == "continue") {
            return new Continue();
        } else if (name == "do_while") {
            return new DoWhile();
        } else if (name == "forever") {
            return new Forever();
        } else if (name == "int32.load") {
            return new Int32Load();
        } else if (name == "int32.store") {
            return new Int32Store();
        } else if (name == "if") {
            return new If();
        } else if (name == "return") {
            return new Return();
        } else if (name == "get_global") {
            return new GetGlobal(stream, context);
        } else if (name == "set_global") {
            return new SetGlobal(stream, context);
        } else {
            throw UnknownInstructionName(name);
        }
    }

    Instruction *InstructionSet::getInstruction(std::string name, sexpr::SExpr& expr, ModuleContext &context,
                                                       FunctionContext &functionContext, const std::map<std::string, std::size_t>& nameToIndex) {
        // TODO literals
        if (name == "int32.add") {
            return new I32Add();
        } else if (name == "int32.sub") {
            return new I32Sub();
        } else if (name == "int32.mul") {
            return new I32Mul();
        } else if (name == "int32.div") {
            return new I32Div();
        } else if (name == "print") {
            return new Print();
        } else if (name == "call") {
            return new FunctionCall(expr, context);
        } else if (name == "get_local") {
            return new GetLocal(expr, functionContext);
        } else if (name == "block") {
            return new Block(expr);
        } else if (name == "set_local") {
            return new SetLocal(expr, functionContext);
        } else if (name == "break") {
            return new Break();
        } else if (name == "continue") {
            return new Continue();
        } else if (name == "do_while") {
            return new DoWhile();
        } else if (name == "forever") {
            return new Forever();
        } else if (name == "int32.load") {
            return new Int32Load();
        } else if (name == "int32.store") {
            return new Int32Store();
        } else if (name == "if") {
            return new If();
        } else if (name == "return") {
            return new Return();
        } else {
            throw UnknownInstructionName(name);
        }

        // TODO globals
    }
}
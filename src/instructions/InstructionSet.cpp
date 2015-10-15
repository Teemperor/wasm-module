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
#include "Instructions.h"
#include <instructions/Print.h>
#include <instructions/assert/I32AssertReturn.h>

namespace wasm_module {

    inline bool ends_with(std::string const & value, std::string const & ending)
    {
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    Instruction *InstructionSet::getInstruction(std::string name, binary::ByteStream &stream, ModuleContext &context,
                                                FunctionContext &functionContext) {
        if (name == "literal") {
            return new Literal(stream, context);
        } else if (name == "i32.add") {
            return new I32Add();
        } else if (name == "i32.sub") {
            return new I32Sub();
        } else if (name == "i32.mul") {
            return new I32Mul();
        } else if (name == "i32.div_u") {
            return new I32DivSigned();
        } else if (name == "i32.div_s") {
            return new I32DivUnsigned();
        } else if (name == "i32.lt") {
            return new I32LessThanSigned();
        } else if (name == "i32.le") {
            return new I32LessEqualSigned();
        } else if (name == "i32.or") {
            return new I32Or();
        } else if (name == "i32.xor") {
            return new I32Xor();
        } else if (name == "i32.rem_s") {
            return new I32RemainderSigned();
        } else if (name == "i32.rem_u") {
            return new I32RemainderUnsigned();
        } else if (name == "print") {
            return new Print();
        } else if (name == "call_direct") {
            return new Call(stream, context);
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
        } else if (name == "if") {
            return new If();
        } else if (name == "return") {
            return new Return();
        } else {
            throw UnknownInstructionName(name);
        }
    }

    Instruction *InstructionSet::getInstruction(std::string name, const sexpr::SExpr& expr, ModuleContext &context,
                                                       FunctionContext &functionContext) {
        if (name == "i32.add") {
            return new I32Add();
        } else if (name == "i32.sub") {
            return new I32Sub();
        } else if (name == "i32.mul") {
            return new I32Mul();
        } else if (name == "i32.div_u") {
            return new I32DivSigned();
        } else if (name == "i32.div_s") {
            return new I32DivUnsigned();
        } else if (name == "i32.lt") {
            return new I32LessThanSigned();
        } else if (name == "i32.le") {
            return new I32LessEqualSigned();
        } else if (name == "i32.or") {
            return new I32Or();
        } else if (name == "i32.xor") {
            return new I32Xor();
        } else if (name == "i32.rem_s") {
            return new I32RemainderSigned();
        } else if (name == "i32.rem_u") {
            return new I32RemainderUnsigned();
        } else if (name == "print") {
            return new Print();
        } else if (name == "call") {
            return new Call(expr, context);
        } else if (name == "get_local") {
            return new GetLocal(expr, functionContext);
        } else if (name == "set_local") {
            return new SetLocal(expr, functionContext);
        } else if (name == "break") {
            return new Break();
        } else if (name == "continue") {
            return new Continue();
        } else if (name == "do_while") {
            return new DoWhile();
        } else if (name == "i32.assert_return") {
            return new I32AssertReturn();
        } else if (name == "forever") {
            return new Forever();
        } else if (name == "if") {
            return new If();
        } else if (name == "return") {
            return new Return();
        } else if (ends_with(name, ".const")) {
            return new Literal(expr);
        } else {
            throw UnknownInstructionName(name);
        }

        // TODO globals
    }
}
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

namespace wasm_module {

    inline bool ends_with(std::string const & value, std::string const & ending)
    {
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    Instruction *InstructionSet::getInstruction(std::string name, binary::ByteStream &stream, ModuleContext &context,
                                                FunctionContext &functionContext) {
        Instruction* instruction = getInstruction(name, context, functionContext);

        if (instruction) {
            return instruction;
        } else {
            if (name == "literal") {
                return new Literal(stream, context);
            } else if (name == "call_direct") {
                return new Call(stream, context);
            } else if (name == "get_local") {
                return new GetLocal(stream, functionContext);
            } else if (name == "block") {
                return new Block(stream);
            } else if (name == "set_local") {
                return new SetLocal(stream, functionContext);
            } else {
                throw UnknownInstructionName(name);
            }
        }

    }

    Instruction *InstructionSet::getInstruction(std::string name, const sexpr::SExpr& expr, ModuleContext &context,
                                                       FunctionContext &functionContext) {

        Instruction* instruction = getInstruction(name, context, functionContext);

        if (instruction) {
            return instruction;
        } else {
            if (name == "call") {
                return new Call(expr, context);
            } else if (name == "get_local") {
                return new GetLocal(expr, functionContext);
            } else if (name == "set_local") {
                return new SetLocal(expr, functionContext);
            } else if (ends_with(name, ".const")) {
                return new Literal(expr);
            } else {
                throw UnknownInstructionName(name);
            }
        }
    }

    #define INSTRUCTION(INSTRNAME, CLASSNAME) if(name==INSTRNAME){return new CLASSNAME();}

    Instruction* InstructionSet::getInstruction(std::string name, ModuleContext &context,
                                                FunctionContext &functionContext) {
        INSTRUCTION("i32.add", I32Add)
        else INSTRUCTION("i32.sub", I32Sub)
        else INSTRUCTION("i32.mul", I32Mul)
        else INSTRUCTION("i32.div_s", I32DivSigned)
        else INSTRUCTION("i32.div_u", I32DivUnsigned)
        else INSTRUCTION("i32.lt", I32LessThanSigned)
        else INSTRUCTION("i32.le", I32LessEqualSigned)
        else INSTRUCTION("i32.or", I32Or)
        else INSTRUCTION("i32.xor", I32Xor)
        else INSTRUCTION("i32.rem_s", I32RemainderSigned)
        else INSTRUCTION("i32.rem_u", I32RemainderUnsigned)

        else INSTRUCTION("i32.load8_s", I32Load8Signed)
        else INSTRUCTION("i32.load8_u", I32Load8Unsigned)
        else INSTRUCTION("i32.load16_s", I32Load16Signed)
        else INSTRUCTION("i32.load16_u", I32Load16Unsigned)
        else INSTRUCTION("i32.load", I32Load)

        else INSTRUCTION("i64.load8_s", I64Load8Signed)
        else INSTRUCTION("i64.load8_u", I64Load8Unsigned)
        else INSTRUCTION("i64.load16_s", I64Load16Signed)
        else INSTRUCTION("i64.load16_u", I64Load16Unsigned)
        else INSTRUCTION("i64.load32_s", I64Load32Signed)
        else INSTRUCTION("i64.load32_u", I64Load32Unsigned)
        else INSTRUCTION("i64.load", I64Load)

        else INSTRUCTION("i32.store8", I32Store8)
        else INSTRUCTION("i32.store16", I32Store16)
        else INSTRUCTION("i32.store", I32Store)

        else INSTRUCTION("i64.store8", I64Store8)
        else INSTRUCTION("i64.store16", I64Store16)
        else INSTRUCTION("i64.store32", I64Store32)
        else INSTRUCTION("i64.store", I64Store)

        else INSTRUCTION("f32.store", F32Store)
        else INSTRUCTION("f64.store", F64Store)

        else INSTRUCTION("print", Print)
        else INSTRUCTION("break", Break)
        else INSTRUCTION("continue", Continue)
        else INSTRUCTION("do_while", DoWhile)
        else INSTRUCTION("forever", Forever)
        else INSTRUCTION("if", If)
        else INSTRUCTION("i32.assert_return", I32AssertReturn)

        else {
            new I32Store8;
            return nullptr;
        }


    }
}
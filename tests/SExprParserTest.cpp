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

#include <cstdint>
#include <binary_parsing/ByteStream.h>
#include <Module.h>
#include <binary_parsing/ModuleParser.h>
#include <cassert>
#include <types/Int32.h>
#include <sexpr_parsing/CharacterStream.h>
#include <sexpr_parsing/SExprParser.h>

int main() {
    std::string str = "(module (memory 0 1))\n"
                      "\t(module)";

    CharacterStream stream(str);

    SExprParser parser(stream);

    SExpr expr = parser.parse();

    assert(expr.children().size() == 2);

    assert(expr.children()[0].children().size() == 2);
    assert(expr.children()[0][0] == "module");
    assert(expr.children()[0][1].children().size() == 3);
    assert(expr.children()[0][1][0] == "memory");
    assert(expr.children()[0][1][1] == "0");
    assert(expr.children()[0][1][2] == "1");

    assert(expr.children()[1][0] == "module");

}
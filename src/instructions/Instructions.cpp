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
}
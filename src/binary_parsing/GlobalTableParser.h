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
 *///
// Created by teemperor on 21.06.15.
//

#ifndef WASMINT_GLOBALTABLEPARSER_H
#define WASMINT_GLOBALTABLEPARSER_H


#include <GlobalTable.h>
#include <TypeTable.h>

namespace wasm_module { namespace binary {

    class GlobalTableParser {

        ByteStream &stream;
        GlobalTable globalTable;
        TypeTable &typeTable_;

    protected:
        GlobalTableParser(ByteStream &stream, TypeTable &typeTable)
                : stream(stream), typeTable_(typeTable) {
        }

        void parseExternGlobals() {
            uint32_t numberOfExternalGlobals = stream.popULEB128();
            for (uint32_t i = 0; i < numberOfExternalGlobals; i++) {
                uint32_t typeData = stream.popULEB128();
                std::string name = stream.readCString();

                const Type* type = typeTable_.getType(typeData);

                globalTable.addGlobal(Global(name, type), false);
            }
        }

        void parseInternGlobals() {
            uint32_t numberOfInternalGlobals = stream.popULEB128();
            for (uint32_t i = 0; i < numberOfInternalGlobals; i++) {
                uint32_t typeData = stream.popULEB128();
                std::string name = stream.readCString();

                const Type* type = typeTable_.getType(typeData);

                globalTable.addGlobal(Global(name, type), true);

            }
        }


        void parse() {
            parseExternGlobals();
            parseInternGlobals();
        }

        GlobalTable getParsedTable() {
            return globalTable;
        }

    public:
        static GlobalTable parse(ByteStream &stream, TypeTable &typeTable) {
            GlobalTableParser parser(stream, typeTable);
            parser.parse();
            return parser.getParsedTable();
        }
    };

}}

#endif //WASMINT_GLOBALTABLEPARSER_H

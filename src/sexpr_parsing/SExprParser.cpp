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

#include "SExprParser.h"

namespace wasm_module { namespace sexpr {

    void SExprParser::parseValues(SExpr &parent, bool allowsEndOfStream) {

        bool exit = false;

        while (!exit) {
            stream_.trimWhitespace();

            if (allowsEndOfStream) {
                if (stream_.reachedEnd()) {
                    return;
                }
            }

            if (stream_.peekChar() == ';') {
                stream_.popChar();
                if (stream_.reachedEnd()) {
                    return;
                }
                // check again for the double semicolon comments
                if (stream_.peekChar() == ';') {
                    stream_.popChar();
                }

                while (true) {
                    if (stream_.reachedEnd()) {
                        return;
                    }
                    if (stream_.peekChar() == '\n') {
                        stream_.popChar();
                        break;
                    }
                    stream_.popChar();
                }
                continue;
            }



            if (stream_.peekChar() == '(') {
                stream_.popChar();
                if (stream_.peekChar() == ';') {
                    stream_.popChar();

                    bool foundSemicolon = false;

                    while (true) {
                        if (stream_.peekChar() == ';') {
                            stream_.popChar();
                            foundSemicolon = true;
                        } else if (stream_.peekChar() == ')') {
                            stream_.popChar();
                            if (foundSemicolon)
                                break;
                        } else {
                            foundSemicolon = false;
                            stream_.popChar();
                        }
                    }
                    continue;
                } else {
                    parseValues(parent.addChild(), false);
                }
            } else if (stream_.peekChar() == '"') {

                stream_.popChar();

                std::string word;

                while (true) {
                    char c = stream_.popChar();
                    if (c != '"') {
                        word.push_back(c);
                    } else {
                        parent.addChild(word);
                        break;
                    }
                }

            } else if (stream_.peekChar() == ')') {
                stream_.popChar();
                exit = true;
            } else {
                std::string word;

                while (true) {
                    char c = stream_.popChar();
                    if (!stream_.isWhitespace(c)) {
                        if (c == ')') {
                            exit = true;
                            parent.addChild(word);
                            break;
                        } else {
                            word.push_back(c);
                        }
                    } else {
                        parent.addChild(word);
                        break;
                    }
                }

            }
        }
    }

    SExpr SExprParser::parse(bool allowExitBeforeEOF) {
        SExpr root;
        parseValues(root, true);
        if (!allowExitBeforeEOF && !stream_.reachedEnd()) {
            throw UnknownDataAtEndOfStream();
        }
        return root;
    }

    SExprParser::SExprParser(CharacterStream &stream) : stream_(stream) {
    }
}}
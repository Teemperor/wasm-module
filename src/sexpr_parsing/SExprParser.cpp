#include "SExprParser.h"

namespace wasm_module {

    void SExprParser::parseValues(SExpr &parent, bool allowsEndOfStream) {

        bool exit = false;

        while (!exit) {
            if (allowsEndOfStream) {
                if (stream_.reachedEnd()) {
                    break;
                }
            }

            stream_.trimWhitespace();

            if (stream_.peekChar() == '(') {
                stream_.popChar();
                parseValues(parent.addChild(), false);
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

    SExpr SExprParser::parse(bool allowExitBeforeEOF = false) {
        SExpr root;
        parseValues(root, true);
        if (!allowExitBeforeEOF && !stream_.reachedEnd()) {
            throw UnknownDataAtEndOfStream();
        }
        return root;
    }

    SExprParser::SExprParser(CharacterStream &stream) : stream_(stream) {
    }
}
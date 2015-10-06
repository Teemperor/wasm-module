#ifndef WASMINT_SEXPRPARSER_H
#define WASMINT_SEXPRPARSER_H


#include "CharacterStream.h"
#include "SExpr.h"

class SExprParser {

    CharacterStream& stream_;

    void parseValues(SExpr& parent, bool allowsEndOfStream) {

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

                while(true) {
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

public:
    SExprParser(CharacterStream& stream) : stream_(stream) {
    }

    SExpr parse() {
        SExpr root;
        parseValues(root, true);
        return root;
    }

};


#endif //WASMINT_SEXPRPARSER_H
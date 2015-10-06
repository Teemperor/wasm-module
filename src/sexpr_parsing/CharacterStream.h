#ifndef WASMINT_CHARACTERSTREAM_H
#define WASMINT_CHARACTERSTREAM_H

#include <string>

class UnexpectedEndOfCharacterStream : public std::exception {};

class CharacterStream {

    std::string value_;
    std::size_t position = 0;


public:
    CharacterStream() {
    }
    CharacterStream(std::string value) : value_(value) {
        trimWhitespace();
    }

    char peekChar() const {
        if (position >= value_.size()) {
            throw UnexpectedEndOfCharacterStream();
        }
        return value_[position];
    }

    char popChar() {
        char result = peekChar();
        position++;
        return result;
    }

    bool isWhitespace(char c) {
        return c == ' ' || c == '\n' || c == '\t';
    }

    std::string popWord() {
        std::string result;
        trimWhitespace();
        char c;
        while (!reachedEnd() && !isWhitespace(c = popChar())) {
            result.push_back(c);
        }
        trimWhitespace();
        return result;
    }

    void trimWhitespace() {
        while (!reachedEnd() && isWhitespace(peekChar())) {
            popChar();
        }
    }

    bool reachedEnd() const {
        return position >= value_.size();
    }

};


#endif //WASMINT_CHARACTERSTREAM_H

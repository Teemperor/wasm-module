#ifndef WASMINT_SEXPRPARSER_H
#define WASMINT_SEXPRPARSER_H


#include "CharacterStream.h"
#include "SExpr.h"

namespace wasm_module {

    class UnknownDataAtEndOfStream : public std::exception {
    };

    class SExprParser {

        CharacterStream &stream_;

        void parseValues(SExpr &parent, bool allowsEndOfStream);

    public:
        SExprParser(CharacterStream &stream);

        SExpr parse(bool allowExitBeforeEOF = false);

    };

}

#endif //WASMINT_SEXPRPARSER_H

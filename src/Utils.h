#ifndef WASMINT_UTILS_H
#define WASMINT_UTILS_H

#include <string>
#include <sstream>
#include <regex>
#include "ExceptionWithMessage.h"

namespace wasm_module {

    ExceptionMessage(InvalidNumberLiteral)

    class Utils {

        static const std::regex decNumber;

    public:
        static bool hasDollarPrefix(const std::string& s) {
            if (s.empty())
                return false;
            return s[0] == '$';
        }

        static std::size_t strToSizeT(const std::string& str);

    };
}

#endif //WASMINT_UTILS_H

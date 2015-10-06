#ifndef WASMINT_SEXPR_H
#define WASMINT_SEXPR_H

#include <vector>
#include <string>

namespace wasm_module { namespace sexpr {

    class SExprIsFull : public std::exception {
    };

    class SExprHasNoValue : public std::exception {
    };

    class SExprHasNoChildren : public std::exception {
    };

    class SExpr {

        std::string value_;

        std::vector<SExpr> children_;

    public:
        SExpr() {
        }

        SExpr(std::string value) : value_(value) {
        }

        SExpr &addChild() {
            if (!value_.empty())
                throw SExprIsFull();

            children_.push_back(SExpr());
            return lastChild();
        }

        SExpr &addChild(std::string value) {
            if (!value_.empty())
                throw SExprIsFull();

            children_.push_back(SExpr(value));
            return lastChild();
        }

        SExpr &lastChild() {
            if (!hasChildren())
                throw SExprHasNoChildren();
            return children_.back();
        }

        bool hasChildren() const {
            return !children_.empty();
        }

        bool hasValue() const {
            return !value_.empty();
        }

        const std::string &value() const {
            if (!hasValue()) {
                throw SExprHasNoValue();
            }
            return value_;
        }

        const std::vector<SExpr> &children() const {
            if (!hasChildren())
                throw SExprHasNoChildren();
            return children_;
        }

        const SExpr &operator[](std::size_t i) const {
            if (!hasChildren())
                throw SExprHasNoChildren();
            return children().at(i);
        }

        bool operator==(const std::string &value) const {
            return value_ == value;
        }

    };
}}

#endif //WASMINT_SEXPR_H

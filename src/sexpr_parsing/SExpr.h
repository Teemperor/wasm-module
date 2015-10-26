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

#ifndef WASMINT_SEXPR_H
#define WASMINT_SEXPR_H

#include <vector>
#include <string>
#include <sstream>

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

        SExpr &addChild(const std::string& value) {
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

        bool operator!=(const std::string& otherValue) const {
            return value() != otherValue;
        }

        bool operator==(const std::string& otherValue) const {
            return value() == otherValue;
        }

        std::string toString() const {
            if (hasValue()) {
                return value_;
            } else {
                std::stringstream result;
                result << "(";

                for (const SExpr& child : children_) {
                    result << child.toString();
                    result << " ";
                }

                result << ")";
                return result.str();
            }
        }

    };
}}

#endif //WASMINT_SEXPR_H

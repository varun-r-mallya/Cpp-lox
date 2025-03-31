//
// Created by xeon on 4/1/25.
//

#include "token.h"
#include <string>
#include <sstream>

auto Token::toString() const -> std::string {
    std::ostringstream oss;
    oss << type << " " << lexeme << " ";
    if (literal.has_value()) {
        const std::any &value = literal.value();
        try {
            if (value.type() == typeid(std::string)) {
                oss << std::any_cast<std::string>(value);
            } else if (value.type() == typeid(double)) {
                oss << std::any_cast<double>(value);
            } else if (value.type() == typeid(int)) {
                oss << std::any_cast<int>(value);
            } else if (value.type() == typeid(const char *)) {
                oss << std::any_cast<const char *>(value);
            }
        } catch (const std::bad_any_cast &) {
            oss << "[invalid literal]";
        }
    } else {
        oss << "null";
    }
    return oss.str();
}

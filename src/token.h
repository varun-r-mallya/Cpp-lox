//
// Created by xeon on 4/1/25.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <any>
#include <iostream>
#include <utility>
#include <optional>

enum TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    EndOfFile
};

class Token {
private:
    const TokenType type;
    const std::string lexeme;
    const std::optional<std::any> literal;
    const int line;

public:
    Token(const TokenType type, std::string lexeme, std::optional<std::any> literal, const int line) : type(type),
        lexeme(std::move(lexeme)), literal(std::move(literal)), line(line) {
    };

    [[nodiscard]] std::string toString() const;
};


#endif //TOKEN_H

//
// Created by xeon on 4/1/25.
//

#include "scanner.h"

#include <optional>

#include "token.h"
#include "lox.h"

#include <utility>

Scanner::Scanner(std::string input_source) : source(std::move(input_source)) {
}

bool Scanner::isAtEnd() const {
    return (current >= static_cast<int>(source.length()));
}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    const Token EOFToken(EndOfFile, "", std::nullopt, line);
    tokens.emplace_back(EOFToken);
    return tokens;
}

void Scanner::scanToken() {
    switch (const char c = advance()) {
        case '(':
            addToken(LEFT_PAREN);
            break;
        case ')':
            addToken(RIGHT_PAREN);
            break;
        case '{':
            addToken(LEFT_BRACE);
            break;
        case '}':
            addToken(RIGHT_BRACE);
            break;
        case ',':
            addToken(COMMA);
            break;
        case '.':
            addToken(DOT);
            break;
        case '-':
            addToken(MINUS);
            break;
        case '+':
            addToken(PLUS);
            break;
        case ';':
            addToken(SEMICOLON);
            break;
        case '*':
            addToken(STAR);
            break;
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '/':
            if (match('/')) {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd())
                    advance();
            } else {
                addToken(SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;
        case '\n':
            line++;
            break;
        case '"': String();
            break;
        default:
            if (isDigit(c)) {
                number();
            } else {
                Lox::error(line, "Unexpected character.");
            }
            break;
    }
}

void Scanner::number() {
    while (isDigit(peek())) advance();
    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the "."
        advance();

        while (isDigit(peek())) advance();
    }

    try {
        double value = std::stod(source.substr(start, current - start));
        addToken(TokenType::NUMBER, value);
    } catch (const std::invalid_argument &) {
        Lox::error(line, "Invalid number format.");
    } catch (const std::out_of_range &) {
        Lox::error(line, "Number too large.");
    }
}


auto Scanner::isDigit(const char c) -> bool {
    return c >= '0' && c <= '9';
}

auto Scanner::String() -> void {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        Lox::error(line, "Unterminated string.");
        return;
    }

    // The closing ".
    advance();

    // Trim the surrounding quotes.
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(STRING, value);
}

char Scanner::peekNext() const {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

char Scanner::advance() {
    const char curr = source[current];
    if (!isAtEnd())
        current++;
    return curr;
}

void Scanner::addToken(const TokenType type) {
    addToken(type, std::nullopt);
}

void Scanner::addToken(const TokenType type, std::any literal) {
    const std::string text = source.substr(start, current - start);
    const Token t(type, text, std::move(literal), line);
    tokens.emplace_back(t);
}

bool Scanner::match(const char expected) {
    if (isAtEnd()) {
        return false;
    }
    if (source[current] != expected) {
        return false;
    }
    current++;
    return true;
}

// this uses a concept called lookahead
char Scanner::peek() const {
    if (isAtEnd())
        return '\0';
    return source[current];
}

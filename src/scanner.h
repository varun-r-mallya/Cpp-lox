//
// Created by xeon on 4/1/25.
//

#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include "token.h"

class Scanner {
private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0; // points to the first character of the string being processed
    int current = 0; // points to the current character being processed
    int line = 1; // tracks the source line
    char advance(); // goes one character ahead and returns it
    bool match(char); // Matches characters with EOL error handling inbuilt
    [[nodiscard]] char peek() const;

    static bool isDigit(char c);

    // if it is at the end, then return \0 else returns the current character without consuming it
    [[nodiscard]] bool isAtEnd() const; // just checks if we have reached the EOL
    void String();

    [[nodiscard]] char peekNext() const;

    void number();

public:
    explicit Scanner(std::string input_source);

    std::vector<Token> scanTokens();

    void scanToken();

    void
    addToken(TokenType type, std::any literal);

    void addToken(TokenType type);
};


#endif //SCANNER_H

#include "lox.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

auto runPrompt() -> void {
    Lox lox;
    std::string input_line;
    std::cout << "Cpp-Lox v0.0.1\n";
    while (!lox.getExit()) {
        std::cout << ">>> ";
        std::getline(std::cin, input_line);
        if (input_line.empty()) {
            exit(0);
        }
        Lox::hadError = false;
        lox.run(input_line);
        std::cout << std::endl;
    }
}

auto runFile(const char *fileName) -> int {
    std::ifstream file;
    file.open(fileName, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << fileName << std::endl;
        return -1;
    }
    Lox lox;

    // Read the entire file into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContents = buffer.str();
    file.close();
    lox.run(fileContents);
    if (Lox::hadError) {
        return -1;
    }
    return 0;
}

int main(const int argc, char *argv[]) {
    if (argc > 2) {
        std::cout << "Usage: cpp-lox [script]\n";
        exit(-1);
    } else if (argc == 1) {
        runPrompt();
    } else if (argc == 2) {
        if (!runFile(argv[1])) {
            exit(-1);
        }
    }
}

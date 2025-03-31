//
// Created by xeon on 4/1/25.
//

#include "lox.h"
#include "token.h"
#include "scanner.h"

#include <csignal>
#include <iostream>
#include <vector>

bool Lox::hadError = false;

auto Lox::setExit(const bool inputExit) -> void {
  exit = inputExit;
}

auto Lox::getExit() const -> bool {
  return exit;
}

auto Lox::run(const std::string &source) -> void {
  Scanner scanner(source);
  const std::vector<Token> tokens = scanner.scanTokens();
  for (const auto& token: tokens) {
    std::cout << token.toString() << "\n";
  }
}

void Lox::report(const int line, const std::string &where,
                 const std::string &message) {
  std::cout << "[line " + std::to_string(line) + "] Error" + where + ": " + message << "\n";
  Lox::hadError = true;
}

void Lox::error(const int line, const std::string &message) {
  Lox::report(line, "", message);
}

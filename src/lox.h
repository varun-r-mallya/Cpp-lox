//
// Created by xeon on 3/31/25.
//

#ifndef LOX_H
#define LOX_H

#include<string>

class Lox {
private:
    bool exit = false;

public:
    static bool hadError;

    void setExit(bool inputExit);

    static void report(int line, const std::string &where, const std::string &message);

    static void error(int line, const std::string &message);

    [[nodiscard]] bool getExit() const;

    void run(const std::string &source);
};

#endif //LOX_H

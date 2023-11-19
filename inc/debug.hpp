#pragma once

#include "includes.hpp"

class CyanException : std::exception {
private:
    std::string _msg;
public:
    CyanException(std::string msg) : _msg(msg) {}
    void printMsg(std::string src) {
        std::cout << std::format("[{}] {}", src, _msg) << std::endl;
    }
};

class Debugger {
public:
    static void raise(std::string src, std::string msg) {
        std::cout << std::format("[{}] {}", src, msg) << std::endl;
    }
};
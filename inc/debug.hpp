#pragma once

#include "includes.hpp"

class Debugger {
public:
    static void PrintMessage(std::string moduleName, std::string errorMessage) {
        #ifdef CYANDB_DEBUG
            std::cout << std::format("[{}] {}", moduleName, errorMessage) << std::endl;
        #endif
    }
};
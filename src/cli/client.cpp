#include "includes.hpp"

int main(int argc, char** argv) {
    // Debugger::PrintMessage(FUNCTION_NAME, "start");
    auto checkRet = ClientConsole::CheckParam(argc, argv);
    if(get<0>(checkRet) == false) {
        std::cout << std::format("error: {}", get<2>(checkRet)) << std::endl;
        std::cout << "usage: cyandb [ -h <ip>[:<port>] ] -u <username> [ -p <password> ]" << std::endl;
        return 1;
    }
    ClientConsole clientConsole = get<1>(checkRet);
    // clientConsole.Print();
    
    return 0;
}
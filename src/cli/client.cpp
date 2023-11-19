#include "includes.hpp"

int main(int argc, char** argv) {
    ClientConsole clientConsole;;
    if(clientConsole.ParseParam(argc, argv) == false) {
        std::cout << "usage: cyandb [ -h <ip>[:<port>] ] -u <username> [ -p <password> ]" << std::endl;
        return 1;
    }
    clientConsole.Print();
    return 0;
}
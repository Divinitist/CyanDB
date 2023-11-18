#pragma once

#include "includes.hpp"

class ServerConsole {
public:
    using NetAddress = class NetAddress;
private:
    NetAddress netAddress;
    Database *pSelectedDatabase;
public:
    ServerConsole(NetAddress netAddr, Database* pCurDB) : netAddress(netAddr), pSelectedDatabase(pCurDB) {}
    ServerConsole(NetAddress netAddr, Database CurDB) : netAddress(netAddr), pSelectedDatabase(&CurDB) {}
    ServerConsole(std::string ip, std::string port, Database* pCurDB) : netAddress(NetAddress(ip, port)), pSelectedDatabase(pCurDB) {}
    ServerConsole(std::string ip, std::string port, Database CurDB) : netAddress(NetAddress(ip, port)), pSelectedDatabase(&CurDB) {}
};

class ClientConsole {
public:
    using NetAddress = class NetAddress;
private:
    std::string _username;
    std::string _password;
    NetAddress _netAddr;
public:
    ClientConsole() : _username(""), _password(""), _netAddr("", "") {};

    ClientConsole(std::string username, std::string password, NetAddress netAddr)
        : _username(username), _password(password), _netAddr(netAddr) {}

    ClientConsole(std::string username, std::string password, std::string ip, std::string port)
        : ClientConsole(username, password, NetAddress(ip, port)) {}

    ClientConsole(std::string username, std::string password, IP ip, Port port)
        : ClientConsole(username, password, NetAddress(ip, port)) {}

    void Print() {
        Debugger::PrintMessage("ClientConsole", std::format("username: {}, password: {}, address: {}", _username, _password, _netAddr.getAddress()));
    }

    /**
     * @brief   check the console param and meanwhile initialize a client console
     * @retval  a pair of bool and ClientConsole, bool indicates whether params passed the check: if true, ClientConsole would be initialized; if false, ClientConsole would be initialized with empty strings
    */
    static std::tuple<bool, ClientConsole, std::string> CheckParam(int argc, char** argv) {
        ClientConsole clientConsole;
        auto retf = [](std::string msg) {return std::make_tuple(false, ClientConsole(), msg);};
        for(auto i = 1; i < argc; ++i) {
            std::string cur = argv[i];
            if(cur == "-h") {
                if(i + 1 >= argc)
                    return retf(std::format("parameter of '{}' missed", cur));
                if(clientConsole._netAddr.getAddress().empty() == false)
                    return retf(std::format("duplicated parameter '{}'", cur));

                std::string host = argv[i + 1], ip, port;
                int hostLen = (int) host.length();
                if(host.substr(0, 9) == std::string("localhost")) {
                    ip = "127.0.0.1";
                    if(host[9] == ':') {
                        if(hostLen < 11)
                            return retf("illegal port");
                        for(auto j = 10; j < hostLen; ++j) {
                            if(host[j] < '0' || host[j] > '9')
                                return retf("illegal port");
                            port += host[j];
                        }
                    }
                    else if(hostLen == 9)
                        port = "2501";
                    else
                        return retf("illegal port");
                }
                else {
                    int num = 0, splitPos = hostLen, dotcnt = 0;
                    for(auto j = 0; j < hostLen; ++j) {
                        if(num < 0 || num > 255)
                            return retf("illegal ip");
                        if(host[j] == ':') {
                            splitPos = j;
                            num = 0;
                            if(dotcnt != 3)
                                return retf("illegal ip");
                        }
                        else if(host[j] == '.') {
                            num = 0;
                            dotcnt++;
                            if(dotcnt > 3 && splitPos != hostLen)
                                return retf("illegal port");
                        }
                        else if(host[j] < '0' || host[j] > '9')
                            return retf("illegal port");
                        else if(splitPos == hostLen)
                            num = num * 10 + (host[j] - '0');
                    }

                    if(splitPos < 7)
                        return retf("illegal ip"); // 0.0.0.0:0
                    if(splitPos == hostLen - 1)
                        return retf("illegal port");

                    if(splitPos == hostLen) {
                        if(dotcnt != 3)
                            return retf("illegal ip");
                        ip = host;
                        port = "2501";
                    }
                    else {
                        ip = host.substr(0, splitPos);
                        port = host.substr(splitPos + 1, hostLen - splitPos - 1);
                    }
                }

                clientConsole._netAddr = NetAddress(ip, port);
                ++i;
            }
            else if(cur == "-u") {
                if(i + 1 >= argc)
                    return retf(std::format("parameter of '{}' missed", cur));
                if(clientConsole._username.empty() == false)
                    return retf(std::format("duplicated parameter '{}'", cur));
                clientConsole._username = argv[i + 1];
                ++i;
            }
            else if(cur == "-p") {
                if(i + 1 >= argc)
                    return retf(std::format("parameter of '{}' missed", cur));
                if(clientConsole._password.empty() == false)
                    return retf(std::format("duplicated parameter '{}'", cur));
                clientConsole._password = argv[i + 1];
                ++i;
            }
            else
                return retf(std::format("unrecognized parameter '{}'", cur));
        }
        if(clientConsole._username == "")
            return retf(std::format("username not included"));
        return std::make_tuple(true, clientConsole, "Complete");
    }
};
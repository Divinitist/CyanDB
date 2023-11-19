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
        Debugger::raise("ClientConsole", std::format("username: {}, password: {}, address: {}", _username, _password, _netAddr.getAddress()));
    }

    CyanException dupParamException{"duplicated parameter"},
                  missParamException{"parameter missed"},
                  noUsernameException{"username not included"},
                  wrongAddrFormatException{"wrong address format"},
                  unrecognParamException{"unrecognized parameter"}; // 在类里面不能用圆括号初始化？


    bool ParseParam(int argc, char** argv) {
        try {
            for(auto i = 1; i < argc; ++i) {
                std::string cur = argv[i];
                if(cur == "-h") {
                    if(++i >= argc) throw missParamException;
                    if(_netAddr.getAddress().empty() == false)
                        throw dupParamException;
                    if(_netAddr.ParseAddress(argv[i]) == false)
                        throw wrongAddrFormatException;
                }
                else if(cur == "-u") {
                    if(++i >= argc) throw missParamException;
                    if(_username.empty() == false)
                        throw dupParamException;
                    _username = argv[i];
                }
                else if(cur == "-p") {
                    if(++i >= argc) throw missParamException;
                    if(_password.empty() == false)
                        throw dupParamException;
                    _password = argv[i];
                }
                else throw unrecognParamException;
            }
            if(_username == "") throw noUsernameException;
            return true;
        }
        catch(CyanException& ce) {
            ce.printMsg(FUNCTION_NAME);
            return false;
        }
    }
};
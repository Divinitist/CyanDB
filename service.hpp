#pragma once

#include "includes.hpp"

class Console {
public:
    using NetAddress = NetAddress;
private:
    NetAddress netAddress;
    Database *pSelectedDatabase;
public:
    Console(NetAddress netAddr, Database* pCurDB) : netAddress(netAddr), pSelectedDatabase(pCurDB) {}
    Console(NetAddress netAddr, Database CurDB) : netAddress(netAddr), pSelectedDatabase(&CurDB) {}
    Console(std::string ip, std::string port, Database* pCurDB) : netAddress(NetAddress(ip, port)), pSelectedDatabase(pCurDB) {}
    Console(std::string ip, std::string port, Database CurDB) : netAddress(NetAddress(ip, port)), pSelectedDatabase(&CurDB) {}
};
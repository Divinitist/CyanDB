#pragma once

#include "includes.hpp"


enum IPType{
    IPv4 = 0,
    IPv6 = 1
};

class IP { // 默认IPv4，IPv6后续再考虑
private:
    std::string _ip;
    bool _ipType;
public:
    IP(std::string ip, IPType ipType = IPv4) : _ip(ip), _ipType(ipType) {
        if(ip == "localhost")
            _ip = "127.0.0.1";
    }
};

class Port {
private:
    std::string _port;
public:
    Port(std::string port) : _port(port) {}
};

class NetAddress {
private:
    IP _ip;
    Port _port;
public:
    NetAddress(IP ip, Port port) : _ip(ip), _port(port) {}
    NetAddress(std::string ip, std::string port) : _ip(IP(ip)), _port(Port(port)) {}
};
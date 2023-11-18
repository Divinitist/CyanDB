#pragma once

#include "includes.hpp"

enum IPType{
    IPv4 = 0,
    IPv6 = 1
};

class IP { // 默认IPv4，IPv6后续再考虑
private:
    std::string _ip;
    IPType _ipType;
public:
    IP(std::string ip = "localhost", IPType ipType = IPv4) : _ip(ip), _ipType(ipType) {
        if(ip == "localhost")
            _ip = "127.0.0.1";
    }
    bool operator==(const IP& ip) const {
        return (_ip == ip._ip) && (_ipType == ip._ipType);
    }
    friend class NetAddress;
};

class Port {
private:
    std::string _port;
public:
    Port(std::string port = "2501") : _port(port) {}
    bool operator==(const Port& port) const {
        return _port == port._port;
    }
    friend class NetAddress;
};

class NetAddress {
private:
    IP _ip;
    Port _port;
    std::string _address;
public:
    NetAddress(IP ip, Port port) : _ip(ip), _port(port) {
        if(ip._ip.empty() || port._port.empty()) _address = "";
        else _address = ip._ip + ":" + port._port;
    }
    NetAddress(std::string ip, std::string port) : NetAddress(IP(ip), Port(port)) {}

    std::string getAddress() {
        return _address;
    }

    bool operator==(const NetAddress& netAddr) const {
        return (_ip == netAddr._ip) && (_port == netAddr._port);
    }
    bool operator!=(const NetAddress& netAddr) const {
        return !(*this == netAddr);
    }
};

class TCPConnect {
private:

public:
    TCPConnect() {}
    
};
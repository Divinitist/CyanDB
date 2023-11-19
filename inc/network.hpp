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

    CyanException illegalIPException{"illegal ip"},
                  illegalPortException{"illegal port"};

    bool ParseAddress(const char* argv) {
        try {
            std::string host = argv, ip, port;
            int hostLen = (int) host.length();
            if(host.substr(0, 9) == std::string("localhost")) {
                ip = "127.0.0.1";
                if(host[9] == ':') {
                    if(hostLen < 11)
                        throw illegalPortException;
                    for(auto j = 10; j < hostLen; ++j) {
                        if(host[j] < '0' || host[j] > '9')
                            throw illegalPortException;
                        port += host[j];
                    }
                }
                else if(hostLen == 9)
                    port = "2501";
                else throw illegalPortException;
            }
            else {
                int num = 0, splitPos = hostLen, dotcnt = 0;
                for(auto j = 0; j < hostLen; ++j) {
                    if(num < 0 || num > 255)
                        throw illegalIPException;
                    if(host[j] == ':') {
                        splitPos = j;
                        num = 0;
                        if(dotcnt != 3)
                            throw illegalIPException;
                    }
                    else if(host[j] == '.') {
                        num = 0;
                        dotcnt++;
                        if(dotcnt > 3 && splitPos != hostLen)
                            throw illegalPortException;
                    }
                    else if(host[j] < '0' || host[j] > '9')
                        throw illegalPortException;
                    else if(splitPos == hostLen)
                        num = num * 10 + (host[j] - '0');
                }

                if(splitPos < 7)
                    throw illegalIPException; // 0.0.0.0:0
                if(splitPos == hostLen - 1)
                    throw illegalPortException;

                if(splitPos == hostLen) {
                    if(dotcnt != 3)
                        throw illegalIPException;
                    ip = host;
                    port = "2501";
                }
                else {
                    ip = host.substr(0, splitPos);
                    port = host.substr(splitPos + 1, hostLen - splitPos - 1);
                }
            }
            *this = NetAddress(ip, port);
            return true;
        }
        catch(CyanException& ce) {
            ce.printMsg(FUNCTION_NAME);
            return false;
        }
    }
};

class TCPConnect {
private:

public:
    TCPConnect() {}

};
#pragma once

#include <iostream>
#include <format>
#include <cstring>
#include <regex>
#include <utility>

#define CYANDB_DEBUG
#define FUNCTION_NAME (__func__)

#include "debug.hpp"

#include "database.hpp"
#include "network.hpp"
#include "service.hpp"


//-----------------------------------------------------------NETWORK-------------------------------------------------------------------

class IP;
class Port;
class NetAddress;

//----------------------------------------------------------DATABASE-------------------------------------------------------------------

class Database;
class Table;
class Column;
class Constraint;
class Index;

//-----------------------------------------------------------SERVICE-------------------------------------------------------------------

class ServerConsole;
class ClientConsole;
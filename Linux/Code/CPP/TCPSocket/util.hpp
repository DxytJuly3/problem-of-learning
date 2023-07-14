#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "logMessage.hpp"

#define SOCKET_ERR	1
#define BIND_ERR	2
#define LISTEN_ERR	3
#define USE_ERR		4

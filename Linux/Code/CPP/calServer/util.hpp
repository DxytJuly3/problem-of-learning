#pragma once

#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "logMessage.hpp"

#define SOCKET_ERR	1
#define BIND_ERR	2
#define LISTEN_ERR	3
#define USE_ERR		4
#define CONNECT_ERR 5
#define FORK_ERR	6
#define WAIT_ERR	7

#define BUFFER_SIZE 1024


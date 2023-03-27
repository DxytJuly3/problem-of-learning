// 进程1 和 进程2 都需要包含的头文件
#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define IPC_PATH "./.fifo"              // 命名文件路径
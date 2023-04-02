#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <unistd.h>
#include <cassert>

#define SHM_SIZE 4096
#define PATH_NAME ".fifo"
#define PROJ_ID 0x14

#define FIFO_FILE ".fifo"

// 创建命名管道文件
void CreatFifo() {
    umask(0);
    if(mkfifo(FIFO_FILE, 0666) < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(-1);
    }
}

#define READER O_RDONLY
#define WRITER O_WRONLY

// 以一定的方式打开管道文件
int Open(const std::string &filename, int flags)
{
    return open(filename.c_str(), flags);
}

// 用于服务端, 等待读取管道文件数据, 即读取信号
int Wait(int fd) {
    uint32_t value = 0;
    ssize_t res = read(fd, &value, sizeof(value));
    
    return res;
}

// 用于客户端, 向管道中写入数据, 即写入信号
void Signal(int fd) {
    uint32_t cmd = 1;
    write(fd, &cmd, sizeof(cmd));
}

// 关闭管道文件, 删除管道文件
void Close(int fd, const std::string& filename) {
    close(fd);
    unlink(filename.c_str());
}

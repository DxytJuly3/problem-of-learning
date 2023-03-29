#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 4096
#define PATH_NAME ".ipcShm"
#define PROJ_ID 0x14
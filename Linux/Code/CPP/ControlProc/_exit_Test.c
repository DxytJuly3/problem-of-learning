#include <stdio.h>
#include <unistd.h>

void _exit_Test() {
    _exit(88);
}

int main() {
    printf("I am a Process ");
    _exit_Test();

    return 0;
}


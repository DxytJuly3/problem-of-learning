#include <stdio.h>

int main() {
    extern char **environ;
    for(int i = 0; environ[i]; i++) {
        printf("[%d]: %s\n", i, environ[i]);
    }

    return 0;
}

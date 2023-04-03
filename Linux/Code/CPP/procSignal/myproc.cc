#include <iostream>
#include <unistd.h>
using std::cout;
using std::endl;

int main() {
    while(true) {
        cout << "I am a process, pid:: " << getpid() << endl;
        sleep(1);
    }

    return 0;
}
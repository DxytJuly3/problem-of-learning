#include "myPrint.h"

void myPrint(const char* msg){
    printf("%s:: %d\n", msg, __TIME__);
}
#include "myMath.h"

int addToVal(int from, int to) {
    assert(from <= to);

    int result = 0;
    for(int i = from; i <= to; i++) {
        result += i;
    }

    return result;
}


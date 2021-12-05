//假设你们社团要竞选社长，有两名候选人分别是A和B，社团每名同学必须并且只能投一票，最终得票多的人为社长.
#include <stdio.h>

int main()
{
    char c = 0;
    unsigned int countA = 0;
    unsigned int countB = 0;
    while((c = getchar()) != EOF)
    {
        if(c == 'A')
            countA++;
        else if(c == 'B')
            countB++;
    }
    if(countA > countB)
        printf("A");
    else if(countA < countB)
        printf("B");
    else
        printf("E");
    
    return 0;
}
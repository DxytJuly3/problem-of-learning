//珠玑妙算游戏（the game of master mind）的玩法如下。
//计算机有4个槽，每个槽放一个球，颜色可能是红色（R）、黄色（Y）、绿色（G）或蓝色（B）。
//例如，计算机可能有RGGB 4种（槽1为红色，槽2、3为绿色，槽4为蓝色）。作为用户，你试图猜出颜色组合。
//打个比方，你可能会猜YRGB。要是猜对某个槽的颜色，则算一次“猜中”；要是只猜对颜色但槽位猜错了，则算一次“伪猜中”。注意，“猜中”不能算入“伪猜中”。
//给定一种颜色组合solution和一个猜测guess，编写一个方法，返回猜中和伪猜中的次数answer，其中answer[0]为猜中的次数，answer[1]为伪猜中的次数。

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/master-mind-lcci
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* masterMind(char* solution, char* guess, int* returnSize)
{
    int* answer = (int*)malloc(sizeof(int) * 2);
    *returnSize = 2;
    int Great = 0;
    int great = 0;
    for(int i = 0; i < 4; i++)
    {
        if(solution[i] == guess[i])
        {
            Great++;
            solution[i] = 0;
            guess[i] = 0;
        }
    }
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(solution[i] == guess[j] && solution[i] != 0 && guess[j] != 0)
            {
                great++;
                solution[i] = 0;
                guess[j] = 0;
                break;
            }
        }
    }
    answer[0] = Great;
    answer[1] = great;

    return answer;
}
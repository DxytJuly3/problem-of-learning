/*
链接：https://www.nowcoder.com/questionTerminal/e1bb714eb9924188a0d5a6df2216a3d1
来源：牛客网

给定一个二维数组board，代表棋盘，其中元素为1的代表是当前玩家的棋子，0表示没有棋子，-1代表是对方玩家的棋子。当一方棋子在横竖斜方向上有连成排的及获胜（及井字棋规则），返回当前玩家是否胜出。
测试样例：

[[1,0,1],[1,-1,-1],[1,-1,0]]

返回：true
*/
/*
思路分析：
    井字棋，需要判断 竖着三条、横着三条以及两个对角线内容 是否相同
    如果有子 且相同, 则其中一位玩家获胜, 如果是1, 则当前玩家获胜
*/
class Board {
public:
    bool checkWon(vector<vector<int> > board) {
        /*for(int i = 0; i < board.size(); i++) {
            if((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == 1) ||
               (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == 1))
                return true;
        }
        if((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] == 1) ||
           (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] == 1))
            return true;*/
        // 对于本题来说 井字棋范围很小了, 可以直接手动对比 0 1 2
        // 但是 对于高度深度相等但都很大的二维数组
        // 如果想要对比 就得使用循环, 需要以 O(N)的时间复杂度遍历完整个数组
         
        // 循环判断 横行
        for(int i = 0; i < board.size(); i++) {
            int winFlag = 0;
            for(int j = 0; j < board[i].size() - 1; j++){
                if((board[i][j] != board[i][j+1])) {
                    winFlag++;
                    break;
                }
            }
            if(winFlag == 0 && board[i][1] == 1)
                return true;
        }
        // 循环判断 竖列
        for(int i = 0; i < board.size(); i++) {
            int winFlag = 0;
            for(int j = 0; j < board[i].size()-1; j++){
                if((board[j][i] != board[j+1][i])) {
                    winFlag++;
                    break;
                }
            }
            if(winFlag == 0 && board[0][i] == 1)
                return true;
        }
        // 判断 [0][0] ~ [size-1][size-1] 对角线
        for(int i = 0, j = 0; i < board.size()-1; i++, j++) {
            if((board[i][j] != board[i+1][j+1]))
                break;
            if(i == board.size()-2 && board[0][0] == 1)
                return true;
        }
        // 判断 [0][size-1] ~ [size-1][0] 对角线
        for(int i = 0, j = board.size()-1; i < board.size()-1; i++, j--) {
            if((board[i][j] != board[i+1][j-1]))
                break;
            if(i == board.size()-2 && board[board.size()-1][0] == 1)
                return true;
        }
         
        return false;
    }
};
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int StrToInt(string str)
    {
        long long ret = 0;
        int flag = 1;
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == ' ' || str[i] == '+')
                continue;
            else if (str[0] == '-')
            {
                flag = -1;
                continue;
            }

            if (str[i] >= '0' && str[i] <= '9')
            {
                ret = ret * 10 + (str[i] - '0');
            }
            else
            {
                return 0;
            }
        }

        return flag * ret;
    }
};

int main()
{
    Solution d1;

    int a = d1.StrToInt("+123");
    cout << a << endl;
}
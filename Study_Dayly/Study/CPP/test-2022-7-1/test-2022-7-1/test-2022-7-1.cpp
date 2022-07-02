#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    string strText = "How are you?";
    string strSeparator = " ";
    string strResult;

    int size_pos = 0;
    int size_prev_pos = 0;
    while ((size_pos = strText.find_first_of(strSeparator, size_pos)) != string::npos)
    {
        strResult = strText.substr(size_prev_pos, size_pos - size_prev_pos);
        cout << strResult << " ";
        size_prev_pos = ++size_pos;
    }
    if (size_prev_pos != strText.size())
    {
        strResult = strText.substr(size_prev_pos, size_pos - size_prev_pos);
        cout << strResult << " ";
    }
    cout << endl;

    return 0;
}
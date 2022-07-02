#include <iostream>
using namespace std;

//namespace July
//{
//	class string
//	{
//	public:
//		string& operator=(const string& str)
//		{
//			if (&str != this)
//			{
//				char* tmp = new char[strlen(str._str) + 1];
//				strcpy(tmp, str._str);
//				strcpy(_str, tmp);
//				delete[] tmp;
//			}
//
//			return *this;
//		}
//	private:
//		char* _str;
//	};
//}

int main()
{
	string s1("123123123");
	s1.resize(20);

	return 0;
}
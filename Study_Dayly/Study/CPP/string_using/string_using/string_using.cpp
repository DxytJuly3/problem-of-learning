#include <iostream>
#include <string>
using namespace std;

void test_constructor()
{
	/* 最常用的 */
	// string()
	string s1;

	// string(const char* s)
	const char* s = "hello world";
	string s2(s);
	string s3("hello world");

	// string(const string & s)
	string s4(s2);
	string s5 = s4;

	/* 没那么常用的 */
	// string(size_t n, char c)
	string s6(10, 'S');

	// string (const char* s, size_t n);
	string s7(s, 4);
	string s8("hello world", 5);

	// string(const string & str, size_t pos, size_t len = npos);
	string s9(s2, 2, 5);
}	

void test_traverse()
{
	string s1("hello world");

	/*for (size_t i = 0; i < s1.size(); i++)
	{
		cout << s1[i];
	}
	cout << endl;*/

	/*string::iterator sIt = s1.begin();
	while (sIt != s1.end())
	{
		cout << *sIt;
		sIt++;
	}
	cout << endl;

	string::reverse_iterator sRIt = s1.rbegin();
	while (sRIt != s1.rend())
	{
		cout << *sRIt;
		sRIt++;
	}
	cout << endl;*/

	for (auto ch : s1)
	{
		cout << ch;
	}
	cout << endl;
}

void test_size_capacity()
{
	/*string s1("hello world");*/

	/*int s1_Size = s1.size();
	cout << s1_Size << endl;

	int s1_Len = s1.length();
	cout << s1_Len << endl;

	size_t s1_Capacity = s1.capacity();
	cout << s1_Capacity << endl;*/

	/*string s2;
	if (s2.empty())
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}

	if (s1.empty())
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}*/

	/*string s1("hello world");
	size_t s1_Size = s1.size();
	cout << s1_Size << endl;

	s1.clear();
	s1_Size = s1.size();
	cout << s1_Size << endl;*/

	/*string s1("hello world");

	s1.reserve(10000);
	size_t s1_Size = s1.size();
	cout << "s1_Size:: " << s1_Size << endl;
	size_t s1_Capacity = s1.capacity();
	cout << "s1_Capacity:: " << s1_Capacity << endl;

	s1.reserve(5);
	s1_Size = s1.size();
	cout << "s1_Size:: " << s1_Size << endl;
	s1_Capacity = s1.capacity();
	cout << "s1_Capacity:: " << s1_Capacity << endl;*/

	/*string s1("hello world");
	s1.resize(1);*/

	string s1("hello world");
	size_t max_Size = s1.max_size();
	cout << max_Size << endl;
}

void test_change()
{
	/*string s1("hello world");
	cout << "push_back before::" << endl;
	cout << "s1.size::  " << s1.size() << endl;
	cout << "s1.capacity::  " << s1.capacity() << endl;
	cout << "s1::  " << s1 << endl << endl;

	for (int i = 0; i < 10; i++)
	{
		s1.push_back('!');
	}
	cout << "push_back after::" << endl;
	cout << "s1.size::  " << s1.size() << endl;
	cout << "s1.capacity::  " << s1.capacity() << endl;
	cout << "s1::  " << s1 << endl;*/

	//string& append(const string & str);
	//用 string类追加字符串
	//string s1("hello world");
	//string s2("!!!!");
	//s1.append(s2);
	//cout << s1 << endl << endl << endl;

	////string& append(const string & str, size_t subpos, size_t sublen);
	//// 用 string类中字符串的pos位置向后len个字符 追加
	//string s3("hello world ");
	//s3.append(s3, 6, 5);
	//cout << s3 << endl << endl << endl;

	////string & append(const char* s);
	//// C类字符串追加
	//string s4("hello world ");
	//s4.append("!!!!");
	//cout << s4 << endl << endl << endl;

	////string& append(const char* s, size_t n);
	//// C类字符串的前n个字符
	//string s5("hello world ");
	//s5.append("!!!!!!!!!!!!!!", 5);
	//cout << s5 << endl << endl << endl;

	////string& append(size_t n, char c);
	//// 追加 n 个 c
	//string s6("hello world ");
	//s6.append(5, 'x');
	//cout << s6 << endl << endl << endl;

	/*string s1("hello world");
	s1 += '!';
	s1 += '!';
	s1 += "hahahaha";
	string s2("66666");
	s1 += s2;

	cout << s1 << endl;*/

	/*string s1("hello world");
	const char* ps = s1.c_str();*/

	//string s1("hello world");
	////size_t find (char c, size_t pos = 0) const;
	//size_t e_pos = s1.find('e', 0);

	////size_t find (const char* s, size_t pos = 0) const;
	//size_t ow_pos = s1.find("o w", 0);

	////size_t find (const string& str, size_t pos = 0) const;
	//string s2("rld");
	//size_t s2_pos = s1.find(s2, 0);

	////size_t find (const char* s, size_t pos, size_t n) const;
	//size_t _3pos = s1.find("llod", 0, 3);
	//size_t _4pos = s1.find("llod", 0, 4);

	//cout << e_pos << endl << endl << endl;
	//cout << ow_pos << endl << endl << endl;
	//cout << s2_pos << endl << endl << endl;
	//cout << _3pos << endl << endl << endl;
	//cout << _4pos << endl << endl << endl;

	/*string s1("hello world");
	string s2 = s1.substr(0, 7);
	string s3 = s1.substr(7);

	cout << s2 << endl;
	cout << s3 << endl;*/

	/*string s1("hello world");
	string s2("July");

	s1.swap(s2);
	cout << "s1::  " << s1 << endl;
	cout << "s2::  " << s2 << endl;*/

	/*string s1("hello world");
	s1.erase(0, 3);
	cout << "s1::  " << s1 << endl;
	s1.erase();
	cout << "s1::  " << s1 << endl;*/

	string s1("hello world");

	// string& insert(size_t pos, const string& str);
	string s2("!!!!");
	s1.insert(3, s2);
	cout << s1 << endl << endl << endl;

	// string& insert(size_t pos, const string& str, size_t subpos, size_t sublen);
	string s3("hello world ");
	s3.insert(5, s2, 2, 3);
	cout << s3 << endl << endl << endl;

	// string& insert (size_t pos, const char* s);
	string s4("hello world ");
	s4.insert(1, "!!!!");
	cout << s4 << endl << endl << endl;

	// string& insert(size_t pos, const char* s, size_t n);
	string s5("hello world ");
	s5.insert(4, "!!!!!x!!!!!!!!", 7);
	cout << s5 << endl << endl << endl;

	// string& insert(size_t pos, size_t n, char c);
	string s6("hello world ");
	s6.insert(9, 5, 'x');
	cout << s6 << endl << endl << endl;
}

void test_non_member()
{
	/*string s1("hello world");
	string s("!!!!!");

	string s2 = s1 + s;
	cout << s2 << endl << endl;

	string s3 = s1 + "!x!x!";
	cout << s3 << endl << endl;

	string s4 = "!x!x!" + s1;
	cout << s4 << endl << endl;

	string s5 = s1 + '+';
	cout << s5 << endl << endl;

	string s6 = '+' + s1;
	cout << s6 << endl << endl;
	cout << s1 << endl << endl;*/

	/*string s1("ssss");

	getline(cin, s1, 'x');
	cout << s1 << endl;*/

	string s1;
	cout << "s1::  " << s1 << endl;
	getline(cin, s1);
	cout << "s1::  " << s1 << endl;
}

int main()
{
	test_non_member();

	return 0;
}
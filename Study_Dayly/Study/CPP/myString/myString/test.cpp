#include "myString.h"

int main()
{
	July::string s1("hello world");
	July::string s2;
	s2 = "July";
	cout << "s1::  " << s1 << endl;
	cout << "s2::  " << s2 << endl;

	s1 += s2;
	s2 += s1;
	cout << "s1::  " << s1 << endl;
	cout << "s2::  " << s2 << endl;

	cout << "ÊäÈës1::";
	cin >> s1;
	cout << "ÊäÈës2::";
	cin >> s2;
	cout << endl << "s1::  " << s1 << endl;
	cout << "s2::  " << s2 << endl;

	s1.clear();
	s2.clear();
	cout << "s1::  " << s1 << endl;
	cout << "s2::  " << s2 << endl;

	return 0;
}
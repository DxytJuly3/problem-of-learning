#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
#include "class_Stack.h"
using namespace std;

class User
{
public:
	void Init(const char* name, const char* sex, const char* tele, int age)
	{
		strcpy(_name, name);
		strcpy(_sex, sex);
		strcpy(_tele, tele);
		_age = age;
	}
	void Print()
	{
		cout << _name << "  " << _sex << "  " << _tele << "  " << _age << endl;
	}
	void Printthis()
	{
		cout << "this:: " << this << endl;
	}

private:
	char _name[20];
	char _sex[10];
	char _tele[20];
	int _age;
};

int main()
{
	User U;
	U.Init("ÆßÔÂ", "ÄÐ", "151********", 20);

	return 0;
}
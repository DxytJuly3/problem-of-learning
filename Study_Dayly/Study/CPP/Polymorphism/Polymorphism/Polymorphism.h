#pragma once
#include <iostream>
using namespace std;

//
class Person
{
public:
	virtual Person* buyTicket() {
		cout << "一般成年人：买票    全价————80￥" << endl;
		return this;
	}
};

class Student : public Person
{
public:
	virtual Student* buyTicket(){
		cout << "在校学生  ：买票    半价————40￥" << endl;
		return this;
	}
};

class Elderly : public Person
{
	virtual Elderly* buyTicket(){
		cout << "老年人    ：买票    免票————0￥" << endl;
		return this;
	}
};

//class Person
//{
//public:
//	virtual Person& buyTicket() {
//		cout << "一般成年人：买票    全价————80￥" << endl;
//		return *this;
//	}
//};
//
//class Student : public Person
//{
//public:
//	virtual Student& buyTicket() {
//		cout << "在校学生  ：买票    半价————40￥" << endl;
//		return *this;
//	}
//};
//
//class Elderly : public Person
//{
//	virtual Elderly& buyTicket() {
//		cout << "老年人    ：买票    免票————0￥" << endl;
//		return *this;
//	}
//};
//
//class Soldier : public Person
//{
//public:
//	virtual Soldier& buyTicket() {
//		cout << "军人      ：买票    优先预定购票——半价————40￥" << endl;
//		return *this;
//	}
//};

//void BuyTicket(Person& per)
//{
//	per.buyTicket();
//}


//class Person
//{
//public:
//	virtual ~Person() {
//		cout << "~Person():: 析构Person对象" << endl;
//	}
//};
//
//class Student : public Person
//{
//public:
//	virtual ~Student(){
//		cout << "~Student():: 析构Student对象" << endl;
//	}
//};
//
//class Elderly : public Person
//{
//public:
//	virtual ~Elderly() {
//		cout << "~Elderly():: 析构Elderly对象" << endl;
//	}
//};
//
//class Soldier : public Person
//{
//public:
//	virtual ~Soldier() {
//		cout << "~Soldier():: 析构Soldier对象" << endl;
//	}
//};
//
//void _Destructor(Person* per)
//{
//	delete per;
//	cout << endl;
//}

//class Base1 {
//public:
//	virtual void func1() {
//		cout << "Base1::func1" << endl;
//	}
//	virtual void func2() {
//		cout << "Base1::func2" << endl;
//	}
//private:
//	int b1;
//};
//
//class Base2 {
//public:
//	virtual void func1() {
//		cout << "Base2::func1" << endl;
//	}
//	virtual void func2() {
//		cout << "Base2::func2" << endl;
//	}
//private:
//	int b2;
//};
//
//class Derive : public Base1, public Base2 {
//public:
//	virtual void func1() {
//		cout << "Derive::func1" << endl;
//	}
//	virtual void func3() {
//		cout << "Derive::func3" << endl;
//	}
//private:
//	int d1;
//};
//
//typedef void(*VFPTR) ();
//void PrintVTable(VFPTR vTable[])
//{
//	cout << " 虚表地址>" << vTable << endl;
//	for (int i = 0; vTable[i] != nullptr; ++i)
//	{
//		printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
//		VFPTR f = vTable[i];
//		f();
//	}
//	cout << endl;
//}
//
//class Base3
//{
//public:
//	virtual void test1()
//	{
//		cout << "test1" << endl;
//	}
//
//	void test2()
//	{
//		cout << "test2" << endl;
//	}
//};
//

//class A {
//public:
//	A(const char* s) {
//		cout << s << endl;
//	}
//
//	~A() {}
//};
//class B :virtual public A
//{
//public:
//	B(const char* s1, const char* s2)
//		:A(s1)
//	{
//		cout << s2 << endl;
//	}
//};
//
//class C :virtual public A
//{
//public:
//	C(const char* s1, const char* s2)
//		:A(s1)
//	{
//		cout << s2 << endl;
//	}
//};
//
//class D :public B, public C
//{
//public:
//	D(const char* s1, const char* s2, const char* s3, const char* s4)
//		: B(s1, s2)
//		, C(s1, s3)
//		, A(s1)
//	{
//		cout << s4 << endl;
//	}
//};

class Base
{
public:
	virtual void Func1() {
		cout << "Base1:: Func1()" << endl;
	}
	void Func2() {
		cout << "Base1:: Func2()" << endl;
	}
	virtual void Func3() {
		cout << "Base1:: Func3()" << endl;
	}

private:
	int _b1 = 1;
};

class Advanced :public Base
{
public:
	virtual void Func1() {
		cout << "Advanced:: Func1()" << endl;
	}
	virtual void ADFunc() {
		cout << "Advanced:: ADFunc()" << endl;
	}

private:
	int _b2 = 2;
};


class Clothes
{
public:
	virtual void Wear() = 0;
};

class Jacket : public Clothes
{
public:
	virtual void Wear()
	{
		cout << "上身" << endl;
	}
};

class Pants : public Clothes
{
public:
	virtual void Wear()
	{
		cout << "下身" << endl;
	}
};
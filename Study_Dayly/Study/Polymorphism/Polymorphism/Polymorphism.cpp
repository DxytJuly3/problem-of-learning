#include <iostream>
using namespace std;

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
	virtual Student* buyTicket(int) override {
		cout << "在校学生  ：买票    半价————40￥" << endl;
		return this;
	}
};

class Elderly : public Person
{
	virtual Elderly* buyTicket() override {
		cout << "老年人    ：买票    免票————0￥" << endl;
		return this;
	}
};

class Soldier : public Person
{
public:
	virtual Soldier* buyTicket() {
		cout << "军人      ：买票    优先预定购票——半价————40￥" << endl;
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

int main()
{/*
	Person* Per = new Person;
	Student* Stu = new Student;
	Elderly* Eld = new Elderly;
	Soldier* Sol = new Soldier;

	_Destructor(Per);
	_Destructor(Stu);
	_Destructor(Eld);
	_Destructor(Sol);*/

	/*Person Per;
	Student Stu;
	Elderly Eld;
	Soldier Sol;

	BuyTicket(Per);
	BuyTicket(Stu);
	BuyTicket(Eld);
	BuyTicket(Sol);*/

	return 0;
}
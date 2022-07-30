#include "Polymorphism.h"

//int main()
//{/*
//	Person* Per = new Person;
//	Student* Stu = new Student;
//	Elderly* Eld = new Elderly;
//	Soldier* Sol = new Soldier;
//
//	_Destructor(Per);
//	_Destructor(Stu);
//	_Destructor(Eld);
//	_Destructor(Sol);*/
//
//	/*Person Per;
//	Student Stu;
//	Elderly Eld;
//	Soldier Sol;
//
//	BuyTicket(Per);
//	BuyTicket(Stu);
//	BuyTicket(Eld);
//	BuyTicket(Sol);*/
//
//	return 0;
//}


//int main()
//{
//	// 这两句取成员函数地址的语句可能不对
//	printf("%p \n", &Derive::func1);
//	printf("%p \n", &Derive::func3);
//
//	Derive d;
//	VFPTR* vTableb1 = (VFPTR*)(*(int*)&d);
//	PrintVTable(vTableb1);
//	VFPTR* vTableb2 = (VFPTR*)(*(int*)((char*)&d + sizeof(Base1)));
//	PrintVTable(vTableb2);
//	return 0;
//}


//int main() {
//	D* p = new D("class A", "class B", "class C", "class D");
//	delete p;
//
//	return 0;


//int main()
//{
//	//Clothes clo;
//	Jacket jac;
//	Pants pan;
//
//	Clothes* ptrC = &jac;
//	ptrC->Wear();
//
//	ptrC = &pan;
//	ptrC->Wear();
//
//	return 0;
//}

//class A
//{
//public:
//	virtual void func(int val = 1) {
//		cout << "A->" << val << endl;
//	}
//
//	virtual void test() {
//		func();
//	}
//};
//class B : public A
//{
//public:
//	virtual void func(int val = 0) {
//		cout << "B->" << val << endl;
//	}
//};
//
//int main()
//{
//	A A;
//	B* p = new B;
//	p->test();
//
//	p->func();
//
//	return 0;
//}
//
typedef void(*VFTPTR)();
void PrintVTable(VFTPTR vTable[])
{
	// 依次取虚表中的虚函数指针打印并调用。调用就可以看出存的是哪个函数
	cout << " 虚表地址>" << vTable << endl;
	for (int i = 0; vTable[i] != nullptr; ++i)
	{
		printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
		VFTPTR f = vTable[i];
		f();
	}
	cout << endl;
}
//
//int main()
//{
//	Advanced adv;
//
//	VFTPTR* vTable = (VFTPTR*)(*(int*)&adv);
//
//	PrintVTable(vTable);
//
//	return 0;
//}

//
//int main()
//{
//	Person per1;
//	Student stu1;
//	Elderly eld1;
//
//	Person* ptrPer = &stu1;
//	Person& quoPer1 = eld1;
//
//	ptrPer->buyTicket();
//	quoPer1.buyTicket();
//
//	ptrPer = &eld1;
//	Person& quoPer2 = stu1;
//
//	ptrPer->buyTicket();
//	quoPer2.buyTicket();
//
//	return 0;
//}
//
//int main()
//{
//	Base* ptrBas = new Advanced;
//
//	ptrBas->Func1();
//	ptrBas->Func2();
//
//	return 0;
//}

//int main()
//{
	//Advanced adv;
	//// 取对象头4个字节地址
	//VFTPTR* vTable1 = (VFTPTR*)(*(int*)&adv);
	//// 取对象第二个父类部分的 头4个字节的地址
//	VFTPTR* vTable2 = (VFTPTR*)(*(int*)((char*)&adv + sizeof(Base1)));
//
//	PrintVTable(vTable1);
//	PrintVTable(vTable2);
//
//	Base1* ptr1 = &adv;
//	Base2* ptr2 = &adv;
//
//	ptr1->func1();
//	ptr2->func1();
//
//	return 0;
//}

//void Func(Elementary* ptrElem)
//{
//	ptrElem->func1();
//	ptrElem->func2();
//}
//
//void Func(Elementary Elem)
//{
//	Elem.func1();
//	Elem.func2();
//}
//
//int main()
//{
//	Intermediate inte;
//	Elementary* elem;
//
//	Elementary::func3();
//
//	/*Func(&inte);
//	Func(inte);*/
//
//	return 0;
//}

int a = 0;

int main()
{
	Elementary* elem = new Elementary;
	VFTPTR* vTable = (VFTPTR*)(*(int*)&elem);

	static int b = 1;
	int c = 0;
	const char* ptrS = "hello";
	cout << "静态区存储变量 a的地址：" << &a << endl;
	cout << "静态区存储变量 b的地址：" << &b << endl;
	cout << "栈区存储变量 c的地址：" << &c << endl;
	printf("常量区存储的地址：%p\n", ptrS);
	cout << "堆区存储对象 elem的地址：" << elem << endl;
	cout << "虚表地址：" << *vTable << endl;

	return 0;
}
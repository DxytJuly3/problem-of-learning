#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
using std::cout;
using std::endl;

int main(int argc, char *argv[], char *env[]) {
	char *User = getenv("USER");
	if(strcmp("July", User) == 0) {
		// 程序功能代码：……
		cout << "可以执行" << endl;
	}
	else {
		cout << "用户错误" << endl;
	}
//	char *Var = getenv("SHELL");
//	cout << Var << endl;
//	for(int i = 0; env[i]; i++) {
//		cout << env[i] << endl;
//	}
//	
//	extern char **environ;
//	for(int i = 0; environ[i]; i++) {
//		cout << environ[i] << endl;
//	}
//  if(argc != 4) {			// 
// 		cout << "./myCalc [-a|-s|-m|-d] one_data two_data" << endl;		// a=add, s=sub, m=mul, d=div
// 		return -1;
// 	}
// 	
// 	int one_data = atoi(argv[2]);		// 
// 	int two_data = atoi(argv[3]);
// 
// 	if(strcmp("-a", argv[1]) == 0) {
// 		cout << one_data << " + " << two_data << " = " << one_data + two_data << endl;
// 	}
// 	else if(strcmp("-s", argv[1]) == 0) {
// 		cout << one_data << " - " << two_data << " = " << one_data - two_data << endl;
// 	}
// 	else if(strcmp("-m", argv[1]) == 0) {
// 		cout << one_data << " * " << two_data << " = " << one_data * two_data << endl;
// 	}
// 	else if(strcmp("-d", argv[1]) == 0) {
// 		if(two_data != 0) {
// 			cout << one_data << " / " << two_data << " = " << one_data / two_data << endl;
// 		}
// 		else {
// 			cout << "two_data is wrong" << endl;
// 		}
// 	}
// 	else {
// 		cout << "./myCalc [-a|-s|-m|-d] one_data two_data" << endl;
// 		return -1;
// 	}

	return 0;
}

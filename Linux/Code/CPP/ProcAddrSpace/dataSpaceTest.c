#include <stdio.h>
#include <stdlib.h>

int global_Var;
int init_global_Var = 1;

int main() {
	static int static_Var = 1;
	char* stack_data1 = (char*)malloc(100);
	char* stack_data2 = (char*)malloc(100);
	char* stack_data3 = (char*)malloc(100);
	char* stack_data4 = (char*)malloc(100);
	printf("main              addr:: %p\n", main);
	printf("global_Var        addr:: %p\n", &global_Var);
	printf("init_global_Var   addr:: %p\n", &init_global_Var);
	printf("static_Var        addr:: %p\n", &static_Var);
	printf("stack_data1       addr:: %p\n", &stack_data1);	
	printf("stack_data2       addr:: %p\n", &stack_data2);	
	printf("stack_data3       addr:: %p\n", &stack_data3);	
	printf("stack_data4       addr:: %p\n", &stack_data4);
	printf("heap_data1        addr:: %p\n", stack_data1);
	printf("heap_data2        addr:: %p\n", stack_data2);
	printf("heap_data3        addr:: %p\n", stack_data3);
	printf("heap_data4        addr:: %p\n", stack_data4);

	return 0;
}

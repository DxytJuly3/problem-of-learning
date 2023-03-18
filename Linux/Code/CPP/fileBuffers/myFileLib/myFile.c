#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

// 缓冲区大小
#define SIZE 1024

// 宏定义缓冲策略, 以便执行
#define NONE_FLUSH 0x0
#define LINE_FLUSH 0x1
#define FULL_FLUSH 0x2

typedef struct _myFILE {
	int _fileno;			// 首先需要存储文件的fd
	char _buffer[SIZE];		// 设置一个1024字节的缓冲区
	int _end;				// 用来记录缓冲区目前长度, 即结尾
	int _flags;				// 用来选择缓冲区刷新策略
}myFILE;

myFILE* my_open(const char* filename, const char* method) {
	// 两个参数, 一个文件名, 一个打开模式
	 
	assert(filename);
	assert(method);
	
	int flag = O_RDONLY;	//打开文件方式 默认只读

	if(strcmp(method, "r") == 0) {}		// 只读传参, 不对flag做修改
	else if(strcmp(method, "r+") == 0) {
		flag = O_RDWR;		// 读写, 文件不存在打开失败
	}
	else if(strcmp(method, "w") == 0) {
		flag = O_WRONLY | O_CREAT | O_TRUNC;		// 清空只写, 文件不存在创建文件
	}
	else if(strcmp(method, "w+") == 0) {
		flag = O_RDWR | O_CREAT | O_TRUNC;
	}
	else if(strcmp(method, "a") == 0) {
		flag = O_WRONLY | O_CREAT | O_APPEND;		// 追加只写, 文件不存在创建文件
	}
	else if(strcmp(method, "a+") == 0) {
		flag = O_RDWR | O_CREAT | O_APPEND;
	}

	int fileno = open(filename, flag, 0666);		// 封装系统接口打开文件
	if(fileno < 0) {
		return NULL;	// 打开文件失败
	}

	// 打开文件成功, 则为myFILE开辟空间
	myFILE* fp = (myFILE*)malloc(sizeof(myFILE));	// 有开辟失败的可能
	if(fp == NULL) {
		return fp;
	}
	memset(fp, 0, sizeof(myFILE));		// 将开辟的空间全部置0
	fp->_fileno = fileno;				// 更新 myFILE里的_fileno
	fp->_flags |= LINE_FLUSH;			// 默认行刷新
	fp->_end = 0;						// 默认缓冲区为空

	return fp;
}

void my_fflush(myFILE* fp) {
	assert(fp);

	if(fp->_end > 0) {		// _end记录的是 缓冲区内数据的长度
		write(fp->_fileno, fp->_buffer, fp->_end);		// 向fd中写入缓冲区数据
		// 这里不在判断是否写入成功
		fp->_end = 0;
		syncfs(fp->_fileno);		// 我们只向fd内核中写入了数据, 数据可能存储到了操作系统中 文件系统的缓冲区中, 需要刷新一下文件系统的缓冲区
									// 与文件缓冲区不同
	}
}

void my_fclose(myFILE* fp) {		// 暂时忽略返回值
	// 再关闭文件之前, 需要先刷新缓冲区, 所以可以先写一个刷新缓冲区的函数
	my_fflush(fp);
	close(fp->_fileno);			// 封装系统接口close()关闭文件
	free(fp);					// 记得free掉 malloc出来的空间
}

void my_fwrite(myFILE* fp, const char* start, int len) {
	assert(fp);
	assert(start);
	assert(len > 0);

	strncpy(fp->_buffer + fp->_end, start, len);		// 将start 追加到_buffer原内容之后
	fp->_end += len;					// 更新一下 _end;

	// 刷新缓冲区
	if(fp->_flags & NONE_FLUSH) {
		// 无缓冲
		my_fflush(fp);
	}
	else if(fp->_flags & LINE_FLUSH) {
		// 行刷新
		if(fp->_end > 0 && fp->_buffer[fp->_end-1] == '\n') {	// 需要访问_end-1位置, 所以要先判断_end > 0 
			my_fflush(fp);
		}
	}
	else if(fp->_flags & FULL_FLUSH) {
		if(fp->_end == SIZE) {				// SIZE是缓冲区的大小
			my_fflush(fp); 
		}
	}
}


int main() {
	myFILE* pf = my_open("newlog.txt", "a+");

	const char* buf1 = "Hello world, hello July";
	const char* buf2 = "Hello world, hello July\n";

	my_fwrite(pf, buf2, strlen(buf2));
	my_fwrite(pf, buf1, strlen(buf1));

	my_fflush(pf);

	return 0;
}

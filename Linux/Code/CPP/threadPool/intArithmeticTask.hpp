#pragma once

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <pthread.h>
#include <unistd.h>
#include "logMessage.hpp"

std::map<char, std::function<int(int, int)>> opFunctions{
	{'+', [](int elemOne, int elemTwo) { return elemOne + elemTwo; }},
	{'-', [](int elemOne, int elemTwo) { return elemOne - elemTwo; }},
	{'*', [](int elemOne, int elemTwo) { return elemOne * elemTwo; }},
	{'/',
	 [](int elemOne, int elemTwo) {
		 if (elemTwo == 0) {
			 std::cout << "div zero, abort" << std::endl;
			 return -1;
		 }
		 return elemOne / elemTwo;
	 }},
	{'%', [](int elemOne, int elemTwo) {
		 if (elemTwo == 0) {
			 std::cout << "div zero, abort" << std::endl;
			 return -1;
		 }
		 return elemOne % elemTwo;
	 }}};

class Task {
public:
	Task(int one = 0, int two = 0, char op = '0')
		: _elemOne(one)
		, _elemTwo(two)
		, _operator(op) {}

	void operator()() {
		run();
	}

	void run() {
		int result = 0;
		if (opFunctions.find(_operator) != opFunctions.end()) {
			result = opFunctions[_operator](_elemOne, _elemTwo);
			if ((_elemTwo == 0 && _operator == '/') ||(_elemTwo == 0 && _operator == '%')) 
				return;
			logMessage(NOTICE, "新线程[%lu] 完成算术任务: %d %c %d = %d",
					   pthread_self(), _elemOne, _operator, _elemTwo, result);
		}
		else {
			std::cout << "非法操作: " << _operator << std::endl;
		}
		sleep(1);
	}

	void get(int* e1, int* e2, char* op) {
		*e1 = _elemOne;
		*e2 = _elemTwo;
		*op = _operator;
	}

private:
	int _elemOne;
	int _elemTwo;
	char _operator;
};

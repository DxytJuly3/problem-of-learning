#pragma once
#include <iostream>
#include <string>

class Task {
public:
    Task(int one = 0, int two = 0, char op = 0)
        : elemOne_(one)
        , elemTwo_(two)
        , operator_(op) {}

    // 仿函数定义
    int operator()() {
        return run();
    }

    int run() {
        int result = 0;
        switch (operator_) {
        case '+':
            result = elemOne_ + elemTwo_;
            break;
        case '-':
            result = elemOne_ - elemTwo_;
            break;
        case '*':
            result = elemOne_ * elemTwo_;
            break;
        case '/': 
            // 除0处理
            if (elemTwo_ == 0) {
                std::cout << "div zero, abort" << std::endl;
                result = -1;
            }
            else {
                result = elemOne_ / elemTwo_;
            }
            break;
        case '%': 
            // 除0处理
            if (elemTwo_ == 0) {
                std::cout << "mod zero, abort" << std::endl;
                result = -1;
            }
            else {
                result = elemOne_ % elemTwo_;
            }
            break;
        default:
            std::cout << "非法操作: " << operator_ << std::endl;
            break;
        }

        return result;
    }

    int get(int* e1, int* e2, char* op) {
        *e1 = elemOne_;
        *e2 = elemTwo_;
        *op = operator_;

        return 0;
    }

private:
    int elemOne_;
    int elemTwo_;
    char operator_;
};
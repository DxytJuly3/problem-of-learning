//#include <iostream>
//
//using std::cout;
//using std::endl;
//using std::cin;
//
//double Division(int a, int b) {
//    // 当b == 0时抛出异常
//    if (b == 0) {
//        try {
//            throw "Division by zero condition!";
//        }
//        catch (const char errmsg) {
//            cout << "Division 捕获了 const char* 异常: " << errmsg << endl;
//			return 1;
//        }
//    }
//    else
//        return ((double)a / (double)b);
//}
//
//void Func() {
//    int len, time;
//    cin >> len >> time;
//    try {
//        cout << Division(len, time) << endl;
//    } 
//    catch (const int errI) {
//        cout << "Func 捕获了 const int 异常: " << errI << endl;
//    } 
//    catch (const char* errS) {
//        cout << "Func 捕获了 const char* 异常: " << errS << endl;
//    } 
//}
//
//int main() {
//    try {
//        Func();
//    }
//    catch (const char* errmsg) {
//        cout << "main 捕获了 const char* 异常: " << errmsg << endl;
//    }
//
//    return 0;
//}
//#include <iostream>
//
//using std::cout;
//using std::endl;
//using std::cin;
//
//class Exc1 {
//private:
//    int _excID;
//};
//
//class Exc2 {
//private:
//    int _excID;
//};
//
//double Division(int a, int b) {
//    // 当b == 0时抛出异常
//    if (b == 0) {
//        throw "Division by zero condition!";
//    }
//    else if (b == 1) {
//        throw 1024;
//    }
//    else if (b == 2) {
//        throw 'b';
//    }
//    else if (b == 3) {
//        throw Exc1();
//    }
//    else if (b < 0) {
//        throw Exc2();
//    }
//    else
//        return ((double)a / (double)b);
//}
//
//void Func() {
//    int len, time;
//    cin >> len >> time;
//    try {
//        cout << Division(len, time) << endl;
//    } 
//    catch (const int errI) { 		// 捕获const整型异常
//        cout << "Func 捕获了 const int 异常: " << errI << endl;
//    } 
//    catch (const char errC) {		// 捕获const字符异常
//        cout << "Func 捕获了 const char 异常: " << errC << endl;
//    } 
//}
//
//int main() {
//    while(true) {
//        try {
//            Func();
//        }
//        catch (const char* errmsg) {	// 捕获const字符串异常
//            cout << "main 捕获了 const char* 异常: " << errmsg << endl;
//        }
//        catch (...) {
//            cout << "main 捕获了 未知异常" << endl;
//        }
//    }
//
//    return 0;
//}
//#include <cstddef>
//#include <iostream>
//#include <ostream>
//
//using std::cin;
//using std::cout;
//using std::endl;
//
//class faClass {
//private:
//	size_t _faExcID;
//};
//
//class sonClass: public faClass { 
//private:
//	size_t _sonExcID;
//};
//
//double Division(int a, int b) {
//    // 当b == 0时抛出异常
//    if (b == 0) {
//        throw "Division by zero condition!";
//    }
//    else if (b == 1) {
//        throw faClass();
//    }
//    else if (b < 0) {
//        throw sonClass();
//    }
//    else
//        return ((double)a / (double)b);
//}
//
//void Func() {
//    int len, time;
//    cin >> len >> time;
//    cout << Division(len, time) << endl;
//}
//
//void Func3() {
//    throw "Throw an exception directly!";
//    cout << "hello Func3" << endl;
//}
//
//void Func2() {
//    Func3();
//    cout << "hello Func2" << endl;
//}
//
//void Func1() {
//    Func2();
//    cout << "hello Func1" << endl;
//}
//
//int main() {
////	while (true) {
////		try {
////			Func();
////		}
//////		catch (const char* errmsg) {
//////			cout << errmsg << endl;
//////		}
////		catch (const faClass& e) {
////			cout << "main 捕获到faClass类异常 或 以faClass为基类的派生类异常" << endl;
////		}
////	}
//	try {
//        Func1();
//    }
//    catch (const char* errmsg) {
//        cout << errmsg << endl;
//    }
//    cout << "hello main" << endl;
//
//	return 0;
//}
//

#include <iostream>
#include <string>
#include <unistd.h>

using std::string;
using std::cout;
using std::endl;

class Exception {
public:
    Exception(const string& errmsg, int id) 
        : _errmsg(errmsg)
        , _id(id) 
    {}
    
    virtual string what() const {
        return _errmsg; 
    }

	int getid() const {
		return _id;
	}

protected:
    string _errmsg;
    int _id;
};

class SqlException : public Exception {
public:
    SqlException(const string& errmsg, int id, const string& sql)
        : Exception(errmsg, id)
        , _sql(sql) 
    {}

    virtual string what() const {
        string str = "SqlException:";
        str += _errmsg;
        str += "->";
        str += _sql;

        return str;
    }

private:
    const string _sql;
};

class CacheException : public Exception {
public:
    CacheException(const string& errmsg, int id) 
        : Exception(errmsg, id) 
    {}
    
    virtual string what() const {
        string str = "CacheException:";
        str += _errmsg;

        return str;
    }
};

class HttpServerException : public Exception {
public:
    HttpServerException(const string& errmsg, int id, const string& type)
        : Exception(errmsg, id)
        , _type(type)
    {}

    virtual string what() const {
        string str = "HttpServerException:";
        str += _type;
        str += ":";
        str += _errmsg;

        return str;
    }

private:
    const string _type;
};

void SQLMgr() {
    if (rand() % 7 == 0) {
        throw SqlException("权限不足", 100, "select * from name = '张三'");
    }
    else {
        cout << "SQL Success" << endl;
    }
}

void CacheMgr() {
    if (rand() % 5 == 0) {
        throw CacheException("权限不足", 101);
    }
    else if (rand() % 6 == 0) {
        throw CacheException("数据不存在", 102);
    }
    else {
        cout << "Cache Success" << endl;
    }

    SQLMgr();
}

void HttpServer() {
    if (rand() % 3 == 0) {
        throw HttpServerException("资源请求错误", 103, "get");
    }
    else if (rand() % 4 == 0) {
        throw HttpServerException("权限不足", 104, "post");
    }
    else {
        cout << "Http Success" << endl;
    }

    CacheMgr();
}

void SeedMsg(const string& str) {
    if (rand() % 2 == 0) {
        throw HttpServerException("SeedMsg::网络错误", 105, "put");
    }
    else if (rand() % 4 == 0) {
        throw HttpServerException("SeedMsg::你已经不是对方好友", 106, "post");
    }
    else {
        cout << "消息发送成功！->" << str << endl;
    }
}
//int main() {
//    while (true) {
//        sleep(1);
//        try {
//            HttpServer();
//        }
//        catch (const Exception& e) {
//            // 多态
//            cout << e.what() << endl;
//        }
//        catch (...) {
//            cout << "Unkown Exception" << endl;
//        }
//    }
//    
//    return 0;
//}
int main() {
	srand(time(0));
    while (true) {
        // 此代码中 唯一一个不能跨平台的函数sleep(), 这里用的是 Linux环境
        // Windows 平台 需要将其换为 Sleep(1000);
  		// 并将 头文件 unistd.h 换为 Windows.h
        sleep(1);
        try {
//			SeedMsg("你好啊?");
            for(int i = 1; i <= 10; i++) {
                try {
					SeedMsg("你好啊?");
					break;
                }
                catch (const Exception& e) {
                    if (e.getid() == 105) {
                        // 针对 105 异常处理
						cout << e.what() << endl;
                        cout << "网络错误, 重新发送, 第 " << i << " 次" << endl;
                        continue;
                    }
                    else {
                        // 不是此异常, 重新抛出
                        throw e;
                    }
                }
            }
        }
        catch (const Exception& e) {
            // 多态
            cout << e.what() << endl;
        }
        catch (...) {
            cout << "Unkown Exception" << endl;
        }
    }
    
    return 0;
}

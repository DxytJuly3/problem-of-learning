#include <iostream>
#include <unistd.h>
#include <string>
using std::cout;
using std::string;
using std::cin;

int main()
{
	string pro;
	pro.resize(100, ' ');
	for(int i = 0; i < 100; i++)
	{
		if(i % 2 == 0)
			pro[i] = 'o';
	}
	size_t cnt = 0;
	const char *lable = "|/-\\";
	while(cnt < 100)
	{
		if(cnt > 0)
		{
			pro[++cnt] = 'C';
			pro[cnt-1] = '=';
			pro[0] = '=';
		}
		else
			pro[cnt++] = 'C';

		if(cnt < 14)
		{
			cout << " 加载中:" << '[' << pro << "] " << cnt << "% " << lable[cnt%4];
			cout << '\r';
			cin.sync();
			usleep(50000);
		}
		else if(cnt >= 14 && cnt < 34)
		{
			cout << " 加载中:" << '[' << pro << "] " << cnt << "% " << lable[cnt%4];
			cout << '\r';
			cin.sync();
			usleep(70000);
		}
		else if(cnt == 34)
		{
			cout << " 加载中:" << '[' << pro << "] " << cnt << "% " << lable[cnt%4];
			cout << '\r';
			cin.sync();
			sleep(3);
		}
		else if(cnt < 87 && cnt > 30)
		{
			cout << " 加载中:" << '[' << pro << "] " << cnt << "% " << lable[cnt%4];
			cout << '\r';
			cin.sync();
			usleep(90000);
		}
		else
		{
			cout << " 加载中:" << '[' << pro << "] " << cnt << "% " << lable[cnt%4];
			cout << '\r';
			cin.sync();
			usleep(35000);
		}
	}

	return 0;
}

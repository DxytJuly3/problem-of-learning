/*
  具体思路:
  因为统计CHN个数
  且每一个 C 都可以与 H 组成 CH, 每一个 CH 又都可以与 N 组成 CHN
  所以从 C 开始搜索
  当搜到 C ,则 num_C ++;
  如果下一个是 H ,则 num_CH += num_C;
  如果再下一个是 N, 则 num_CHN += num_CH;
  
  CCCHN
	搜到 C ,则 num_C++;
	因为前三个都是 C , 则 num_C == 3;
	然后搜到 H , 前边的 C 均可以和 此 H 组成 CH 则, num_CH = num_CH + num_C == 0 + 3 == 3;
	然后搜到 N , 前边的所有 CH 均可以和 此 N 组成 CHN, 则 num_CHN = num_CHN + num_CH == 0 + 3 == 3;

  CCHNCHCHN
	搜到 C, 则 num_C++;
	前两个是 C , 则 num_C == 2；
	第三个是 H , 则 num_CH = num_CH + num_C == 2;
	第四个是 N , 前边的所有 CH 均可以和 此 N 组成 CHN, 则 num_CHN = num_CHN + num_CH == 0 + 2 == 2;
	第五个是 C , 则 num_C++ == 3;
	第六个是 H , 前边的 C 均可以和 此 H 组成 CH 则, num_CH = num_CH + num_C == 2 + 3 == 5;
	第七个是 C , 则 num_C++ == 4;
	第八个是 H , 前边的 C 均可以和 此 H 组成 CH 则, num_CH = num_CH + num_C == 5 + 4 == 9;
	第九个是 N , 前边的所有 CH 均可以和 此 N 组成 CHN, 则 num_CHN = num_CHN + num_CH == 2 + 9 == 11;

	所以 CHN 共11个
*/
#include <stdio.h>
//在庆祝祖国母亲70华诞之际，老师给小乐乐出了一个问题。
//大家都知道China的英文缩写是CHN，那么给你一个字符串s，你需要做的是统计s中子序列“CHN”的个数。
//子序列的定义：存在任意下标a < b < c，那么“s[a]s[b]s[c]”就构成s的一个子序列。
//如“ABC”的子序列有“A”、“B”、“C”、“AB”、“AC”、“BC”、“ABC”。
int main()
{
	char str[8001] = { 0 };
	scanf("%s", &str);
	char* ps = str;
	long long num_C = 0;
	long long num_CH = 0;
	long long num_CHN = 0;
	while (*ps)
	{
		if (*ps == 'C')
			num_C++;
		if (*ps == 'H')
			num_CH += num_C;
		if (*ps == 'N')
			num_CHN += num_CH;
		ps++;
	}
	printf("%lld\n", num_CHN);

	return 0;
}
#include <iostream>
#include <cassert>

// 不包括字符串末尾 '\0'
size_t my_strlen(const char* str) {
	assert(str);

	const char* pstr = str;
	while (*pstr) {
		pstr++;
	}

	return pstr - str;
}

// strcpy 不会检测str长度是否超出dest长度
char* my_strcpy(char* dest, const char* src) {
	assert(dest && src);

	char* ret = dest;

//	while (*src) {
//		*dest++ = *src++;
//	}
//	*dest = *src;
	while (*dest++ = *src++) {}

	return ret;
}

// strcat 也不会判断dest之后的长度是否可以容纳 src
char* my_strcat(char* dest, const char* src) {
	assert(dest && src);

	char* ret = dest;

	while (*dest) {
		dest++;
	} // 先找到dest字符串尾
	while (*dest++ = *src++) {}

	return ret;
}

// strcmp: 
// str1 > str2 return 正数
// str1 < str2 return 负数
// str1 == str2 return 0
int my_strcmp(const char* str1, const char* str2) {
	assert(str1 && str2);

	while (*str1 == *str2) {
		if (*str2 == '\0') {
			return 0;
		}
		str1++;
		str2++;
	}

	return *str1 - *str2;
}

// strstr 返回找到的字符串的首地址
char* strstr(const char* str, const char* substr) {
	assert(str && substr);

	if (*substr == '\0') {
		return (char*)str;
	}

	const char* pStr = str;
	while (*pStr) {
		const char* strStart = pStr;
		const char* pSubStr = substr;
		while (*strStart != '\0' && *pSubStr != '\0' &&	*strStart == *pSubStr ) {
			strStart++;
			pSubStr++;
		}
		// 如果退出循环是因为 substr遍历结束, 那么就找到了
		if (*pSubStr == '\0') {
			return (char*)pStr;
		}
		pStr++;
	}

	return nullptr;
}



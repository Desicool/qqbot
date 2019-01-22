#include "Utils.h"
#include "cqp.h"
#include "stdafx.h"
//#include <cstdio>
using namespace std;
const char* transferCQEmotion(int emotionID) 
{
	char str[100];
	sprintf(str, "[CQ:face,id=%d]", emotionID);
	return str;
}

const char* transferCQImage(const char* filename)
{
	char str[100];
	sprintf(str, "[CQ:image,file=%s]", filename);
	return str;
}

const char* UTF82WCS(const char* szU8)
{
	//预转换，得到所需空间的大小;
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);

	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wchar_t* wszString = new wchar_t[wcsLen + 1];

	//转换
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);

	//最后加上'\0'
	wszString[wcsLen] = '\0';


	return (char*)wszString;
}

char* UnicodeToUtf8(const wchar_t* unicode)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = (char*)malloc(len + 1);
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
	return szUtf8;
}
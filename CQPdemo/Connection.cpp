#include "stdafx.h"
#include "Connection.h"
#include <ctime>

Connection::Connection()
{
	/*driver = get_driver_instance();
	con = driver->connect("localhost:3306", "root", "l1728L3sh+");
	con->setSchema("qqbot");*/
}

const char * Connection::getClassTableByQQ(int64_t qqID)
{
	/*pst = con->prepareStatement("select classtable from qquser where qqid=?");
	pst->setString(1, std::to_string(qqID).c_str());
	sql::ResultSet* rs;
	rs = pst->executeQuery();
	while (rs->next()) 
	{
		return rs->getString("classtable").c_str();
	}*/
	std::string path = "table_of_" + std::to_string(qqID) + ".png";
	HANDLE handle = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	if (handle == INVALID_HANDLE_VALUE)
	{
		CloseHandle(handle);
		return "暂未获取到该用户的课程表";
	}
	/*int size = GetFileSize(handle, NULL);
	char* buf = new char(size);
	DWORD byteReadSize;
	ReadFile(handle, buf, size, &byteReadSize, NULL);*/
	std::string ret = "[CQ:image,file=table_of_" + std::to_string(qqID) + ".png]";
	CloseHandle(handle);
	return ret.c_str();
}

const char * Connection::checkin(int64_t qqID)
{
	std::string path = std::to_string(qqID) + "_checkin.txt";
	HANDLE handle = CreateFileA(path.c_str(), 
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ, 
		NULL, 
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	int size = GetFileSize(handle, NULL);
	int days = 0;
	if (size)
	{
		char* buf = new char(size);
		DWORD byteReadSize;
		ReadFile(handle, buf, size, &byteReadSize, NULL);
		int st = 0;
		while (buf[st] != ' ')
		{
			days = days * 10 + buf[st++] - '0';
		}
		st++;
		int year = (buf[st] - '0') * 1000 + (buf[st + 1] - '0') * 100 +
			(buf[st + 2] - '0') * 10 + buf[st + 3] - '0';
		st += 5;
		int month = (buf[st] - '0') * 10 + buf[st + 1] - '0';
		st += 7;
		int day = (buf[st] - '0') * 10 + buf[st + 1] - '0';
		SYSTEMTIME stUTC;
		GetSystemTime(&stUTC);
		if (stUTC.wDay == 1) { days = 1; }
		else if (month == stUTC.wMonth && year == stUTC.wYear) { days++; }
		WCHAR tmp[14];
		wsprintf(tmp, TEXT("%d %d-%d-%d"), days, stUTC.wYear, stUTC.wMonth, stUTC.wDay);

		int iSize;
		char* pszMultiByte;

		//返回接受字符串所需缓冲区的大小，已经包含字符结尾符'\0'
		iSize = WideCharToMultiByte(CP_ACP, 0, tmp, -1, NULL, 0, NULL, NULL); //iSize =wcslen(pwsUnicode)+1=6
		pszMultiByte = (char*)malloc(iSize * sizeof(char)); //不需要 pszMultiByte = (char*)malloc(iSize*sizeof(char)+1);
		WideCharToMultiByte(CP_ACP, 0, tmp, -1, pszMultiByte, iSize, NULL, NULL);
		DWORD byteWritten = 0;
		SetFilePointer(handle, 0, 0, FILE_BEGIN);
		WriteFile(handle,
			pszMultiByte,
			iSize,
			&byteWritten,
			NULL);
	}
	else
	{
		SYSTEMTIME stUTC;
		GetSystemTime(&stUTC);
		WCHAR tmp[14];
		wsprintf(tmp, TEXT("1 %d-%d-%d"), stUTC.wYear, stUTC.wMonth, stUTC.wDay);

		int iSize;
		char* pszMultiByte;

		//返回接受字符串所需缓冲区的大小，已经包含字符结尾符'\0'
		iSize = WideCharToMultiByte(CP_ACP, 0, tmp, -1, NULL, 0, NULL, NULL); //iSize =wcslen(pwsUnicode)+1=6
		pszMultiByte = (char*)malloc(iSize * sizeof(char)); //不需要 pszMultiByte = (char*)malloc(iSize*sizeof(char)+1);
		WideCharToMultiByte(CP_ACP, 0, tmp, -1, pszMultiByte, iSize, NULL, NULL);
		DWORD byteWritten = 0;
		WriteFile(handle,
			pszMultiByte,
			iSize,
			&byteWritten,
			NULL);
	}
	CloseHandle(handle);
	std::string ret = "签到成功，您已成功签到" + std::to_string(days == 0 ? 1 : days) + "天";
	return ret.c_str();
}


Connection::~Connection()
{
}

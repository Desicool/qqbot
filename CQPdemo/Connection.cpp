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
	std::string path = "./data/image/table_of_" + std::to_string(qqID) + ".png";
	DWORD dwAttrib = GetFileAttributesA(path.c_str());
	if( INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		std::string ret = "[CQ:image,file=table_of_" + std::to_string(qqID) + ".png]";
		return ret.c_str();
	}
	return "暂未获取到您的课程表";
	/*int size = GetFileSize(handle, NULL);
	char* buf = new char(size);
	DWORD byteReadSize;
	ReadFile(handle, buf, size, &byteReadSize, NULL);*/
	
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

const char * Connection::queryMoney(int64_t qqID)
{
	std::string path = "money_of_" + std::to_string(qqID) + ".txt";
	HANDLE handle = CreateFileA(path.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	int size = GetFileSize(handle, NULL);
	if (size)
	{
		char* buf = new char(size);
		DWORD byteReadSize;
		ReadFile(handle, buf, size, &byteReadSize, NULL);
		int money = 0;
		for (int i = 0;i < byteReadSize;i++)
		{
			money = money * 10 + buf[i] - '0';
		}
		std::string ret = "您当前的余额为：" + std::to_string(money) + "元";
		CloseHandle(handle);
		return ret.c_str();
	}
	else
	{
		WCHAR tmp[1];
		wsprintf(tmp, TEXT("0"));

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
		CloseHandle(handle);
		return "您当前的余额为：0元";
	}
}

const char * Connection::queryEmail(int64_t qqID)
{
	std::string path = "email_of_" + std::to_string(qqID) + ".txt";
	HANDLE handle = CreateFileA(path.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	int size = GetFileSize(handle, NULL);
	if (size)
	{
		char* buf = new char(size);
		DWORD byteReadSize;
		ReadFile(handle, buf, size, &byteReadSize, NULL);
		std::string str(buf,byteReadSize);
		
		std::string ret = "您未读的邮件有：\n" + str;
		CloseHandle(handle);
		return ret.c_str();
	}
	else
	{
		CloseHandle(handle);
		return "您当前没有未读邮件";
	}
}


Connection::~Connection()
{
}

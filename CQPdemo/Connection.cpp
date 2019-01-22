#include "stdafx.h"
#include "Connection.h"


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
	std::wstring path = L"table_of_" + std::to_wstring(qqID) + L".png";
	HANDLE handle = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	if ((long)handle == ERROR_FILE_NOT_FOUND)
	{
		return "暂未获取到该用户的课程表";
	}
	/*int size = GetFileSize(handle, NULL);
	char* buf = new char(size);
	DWORD byteReadSize;
	ReadFile(handle, buf, size, &byteReadSize, NULL);*/
	std::string ret = "[CQ:image,file=table_of_" + std::to_string(qqID) + ".png]";
	return ret.c_str();
}


Connection::~Connection()
{
}

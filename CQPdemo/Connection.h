#pragma once

class Connection
{
private:
public:
	Connection();
	const char* getClassTableByQQ(int64_t qqID);
	const char* checkin(int64_t qqID);
	const char* queryMoney(int64_t qqID);
	const char* queryEmail(int64_t qqID);
	~Connection();
};

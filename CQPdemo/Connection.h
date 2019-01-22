#pragma once

class Connection
{
private:
public:
	Connection();
	const char* getClassTableByQQ(int64_t qqID);
	~Connection();
};

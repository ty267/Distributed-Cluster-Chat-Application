#include "log.hpp"
#include "connection.hpp"
#include <iostream>
#include <muduo/base/Logging.h>

using namespace std;

Connection::Connection()
{
	// 初始化数据库连接
	_conn = mysql_init(nullptr);
}

Connection::~Connection()
{
	// 释放数据库连接资源
	if (_conn != nullptr)
		mysql_close(_conn);
}

bool Connection::connect(string ip, unsigned short port,
						 string username, string password, string dbname)
{
	// 连接数据库
	MYSQL *p = mysql_real_connect(_conn, ip.c_str(), username.c_str(),
								  password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr;
	// if (p != nullptr)
	// {
	//     // C和C++代码默认的编码字符是ASCII，如果不设置，从MySQL上拉下来的中文显示？
	//     mysql_query(_conn, "set names gbk");
	//     LOG_INFO << "connect mysql success!";
	// }
	// else
	// {
	//     LOG_INFO << "connect mysql fail!";
	// }

	// return p;
}

bool Connection::update(string sql)
{
	// 更新操作 insert、delete、update
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("更新失败:" + sql);
		LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "更新失败!";
		return false;
	}
	return true;
}

MYSQL_RES *Connection::query(string sql)
{
	// 查询操作 select
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("查询失败:" + sql);
		LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "查询失败!";
		return nullptr;
	}
	return mysql_use_result(_conn);
}

// 获取连接
MYSQL *Connection::getConnection()
{
	return _conn;
}
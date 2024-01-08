#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include <queue>
#include <mutex>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <memory>
#include <functional>
#include "connection.hpp"

using namespace std;
/*
实现连接池功能模块
*/
class ConnectionPool
{
public:
	// 获取连接池对象实例
	static ConnectionPool *getConnectionPool();
	// 给外部提供接口，从连接池中获取一个可用的空闲连接
	shared_ptr<Connection> getConnection();

private:
	// 单例#1 构造函数私有化
	ConnectionPool();

	// // 从配置文件中加载配置项
	// bool loadConfigFile();

	// 运行在独立的线程中，专门负责生产新连接
	void produceConnectionTask();

	// 扫描超过maxIdleTime时间的空闲连接，进行对于的连接回收
	void scannerConnectionTask();

	queue<Connection *> _connectionQue; // 存储mysql连接的队列
	mutex _queueMutex;					// 维护连接队列的线程安全互斥锁
	atomic_int _connectionCnt;			// 记录连接所创建的connection连接的总数量
	condition_variable cv;				// 设置条件变量，用于连接生产线程和连接消费线程的通信
};

#endif

#ifndef _ACTIVEMQ_THREAD_POOL_H
#define _ACTIVEMQ_THREAD_POOL_H

#include <decaf/util/concurrent/ThreadPoolExecutor.h>
#include "ActivemqThreadTaskFactory.h"

//	activemq线程池
class ActivemqThreadPool
{
private:
    static ActivemqThreadPool* m_instance;
    //	线程执行队列
	decaf::util::concurrent::ThreadPoolExecutor* 	m_pThreadPoolExecutor;
private:
    ActivemqThreadPool();
public:
    static ActivemqThreadPool* getInstance()
    {
        return m_instance;
    }
public:
	/*
		函数名：InitThreadPoolForActivemq
		形参：
			[in]nNum_	线程数
		功能：初始化线程池
		返回值：
			成功返回true，失败返回false
	*/
	int InitThreadPoolForActivemq(int corePoolSize=200, int maxPoolSize=200, long long keepAliveTime=10000);
	/*
		函数名：UninitThreadPoolForActivemq
		形参：
			无
		功能：线程池反初始化
		返回值：
			无
	*/
	void UninitThreadPoolForActivemq();
	/*
		函数名：ExcuteThread
		形参：
			[in]pFactory_	线程任务对象
		功能：
			执行线程任务
		返回值：
			成功返回RET_OK，失败返回RET_ERR
	*/
	int ExcuteThread(ActivemqThreadTaskFactory* pFactory_);
};

#endif
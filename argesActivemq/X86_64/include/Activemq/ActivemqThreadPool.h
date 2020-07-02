#ifndef _ACTIVEMQ_THREAD_POOL_H
#define _ACTIVEMQ_THREAD_POOL_H

#include <decaf/util/concurrent/ThreadPoolExecutor.h>
#include "ActivemqThreadTaskFactory.h"

//	activemq�̳߳�
class ActivemqThreadPool
{
private:
    static ActivemqThreadPool* m_instance;
    //	�߳�ִ�ж���
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
		��������InitThreadPoolForActivemq
		�βΣ�
			[in]nNum_	�߳���
		���ܣ���ʼ���̳߳�
		����ֵ��
			�ɹ�����true��ʧ�ܷ���false
	*/
	int InitThreadPoolForActivemq(int corePoolSize=200, int maxPoolSize=200, long long keepAliveTime=10000);
	/*
		��������UninitThreadPoolForActivemq
		�βΣ�
			��
		���ܣ��̳߳ط���ʼ��
		����ֵ��
			��
	*/
	void UninitThreadPoolForActivemq();
	/*
		��������ExcuteThread
		�βΣ�
			[in]pFactory_	�߳��������
		���ܣ�
			ִ���߳�����
		����ֵ��
			�ɹ�����RET_OK��ʧ�ܷ���RET_ERR
	*/
	int ExcuteThread(ActivemqThreadTaskFactory* pFactory_);
};

#endif
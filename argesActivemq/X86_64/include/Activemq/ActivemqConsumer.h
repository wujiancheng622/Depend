/*
	文件说明
	功能：		activemq消息消费者实现
	作者：		华伟宏
	修改日志：	2016-07-21创建
*/


#ifndef ACTIVEMQ_CONSUMER_H_
#define	ACTIVEMQ_CONSUMER_H_

#include <cms/Connection.h>
#include <cms/Session.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/ThreadPoolExecutor.h>
#include <cms/Destination.h>
#include <cms/MessageConsumer.h>
#include <decaf/util/concurrent/Mutex.h>
#include <cms/MessageListener.h>
#include <cms/ExceptionListener.h>
#include <activemq/transport/DefaultTransportListener.h>
#include <cms/BytesMessage.h> 
#include <cms/CMSException.h>
#include <decaf/lang/Exception.h>
#include <string>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
class ActivemqConsumer : public cms::ExceptionListener,
                            public cms::MessageListener,
                            public activemq::transport::DefaultTransportListener,
                            public decaf::lang::Runnable
{
public:
	//	连接
    cms::Connection* 			connection;
	//	连接会话
	cms::Session*				session;
private:
	
	//	请求消息的目的地
    cms::Destination* 			m_pRequestDestination;
	//	消息消费者
    cms::MessageConsumer* 		consumer;
	//	主题或队列
    bool 						useTopic;
	//	消息连接URL
    std::string 				brokerURI;
	//	消息容器名称
    std::string 				destURI;
	//	ACK
    bool 						clientAck;
	//	当前任务数	
	long 						numOfMessagingTasks;
	//	线程锁
	decaf::util::concurrent::Mutex 	mutexGeneral;
	//	线程锁
	decaf::util::concurrent::Mutex 	m_mutexMessage;
	//	消息生存时间 ms
	int							m_nAliveTime;
	//	停止消息处理标准
	bool							m_isStop;
private:
    ActivemqConsumer(const ActivemqConsumer&);
    ActivemqConsumer& operator=(const ActivemqConsumer&);

public:
    ActivemqConsumer(const std::string& brokerURI,
                        const std::string& destURI,
                        bool useTopic = false,
                        bool clientAck = false);
    virtual ~ActivemqConsumer();
    /*
		函数名：_Init
		形参：
			无
		功能：
			consumer初始化
		返回值：
			成功返回RET_OK，失败返回RET_ERR
	*/
    int _Init();
	/*
		函数名：Close
		形参：
			无
		功能：对象关闭处理
		返回值：
			无
	*/
    void _Close();
	
	/*
		函数名：isMessageExpired
		形参：
			[in]message		消息对象
		功能：
			判断消息是否过期
		返回值：
			过期返回true，否则返回false
	*/
	bool _IsMessageExpired(const cms::Message* message_);
	/*
		函数名：IncreaseNumOfMessagingTasks
		形参：
			无
		功能：
			消息任务数量递增
		返回值：
			无
	*/
	void _IncreaseNumOfMessagingTasks();
	/*
		函数名：_DecreaseNumOfMessagingTasks
		形参：
			无
		功能：
			消息任务数量-1
		返回值：
			无
	*/
	void _DecreaseNumOfMessagingTasks();
	/*
		函数名：_GetNumOfMessagingTasks
		形参：
			无
		功能：
			获取当前消息任务的数量
		返回值：
			正在处理和待处理的任务总数
	*/
	long _GetNumOfMessagingTasks();
	/*
		函数名：_RunConsumer
		形参：
			无
		功能：
			consumer配置和初始化
		返回值：
			无
	*/
    int runConsumer();
	/*
		函数名：_QueueMessagingTask
		形参：
			[in]strMessage_				待处理的消息字符串
		功能：
			消息任务分配
		返回值：
			无
	*/
	int _QueueMessagingTask(const unsigned char* _pMassage, const int _nLen);
	/*
		函数名：_OnMessage
		形参：
			[in]message_	待处理的消息文本
		功能：
			consumer接收消息处理
		返回值：
			无
	*/
    virtual void onMessage(const cms::Message* message_);

	/*
		函数名：run
		形参：
			无
		功能：响应消息配置及初始化数据
		返回值：
			无
	*/
	virtual void run();
	/*
		函数名：_AdpterMessage
		形参：
			[in]strMessage_				待处理的消息字符串
		功能：请求消息适配
		返回值：
			成功返回RET_OK，失败返回RET_ERR
	*/
	int _AdpterMessage(std::string& strMessage_);
	/*
		函数名：_ExecuteMessagingTask
		形参：
			[in]strMessage_				待处理的消息字符串
		功能：
			执行消息任务
		返回值：
			成功返回RET_OK，失败返回RET_ERR
	*/
	int _ExecuteMessagingTask(std::string& strMessage_);

	/*
		功能:
			判断消费者监听是否存在
		返回值:
			存在返回true，不存在返回false
	*/
	bool IsExistListener();

	virtual void onException(const cms::CMSException& ex AMQCPP_UNUSED) {
        printf("CMS Exception occurred.  Shutting down client.\n");
        exit(1);
    }

    virtual void onException(const decaf::lang::Exception& ex) {
        printf("Transport Exception occurred: %s \n", ex.getMessage().c_str());
    }

    virtual void transportInterrupted() {
        std::cout << "The Connection's Transport has been Interrupted." << std::endl;
    }

    virtual void transportResumed() {
        std::cout << "The Connection's Transport has been Restored." << std::endl;
    }
private:
	/*
		函数名：_Cleanup
		形参：
			无
		功能：
			资源清理
		返回值：
			无
	*/
    void _Cleanup();
};

#endif	//	ACTIVEMQ_CONSUMER_H_


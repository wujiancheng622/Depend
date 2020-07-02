/*
	文件说明
	功能：		activemq的消息生产者定义
	作者：		华伟宏
	修改日志：	2016-07-21创建
*/
#ifndef ACTIVEMQ_PRODUCER_H_
#define ACTIVEMQ_PRODUCER_H_

#include <cms/Connection.h>
#include <cms/Session.h>
#include <list>
#include <decaf/util/concurrent/Mutex.h>

////////////////////////////////////////////////////////////////////////////////
class ActivemqProducer
{
private:
	//	连接
    cms::Connection* connection;
    //	连接会话
    cms::Session* session;
    //	消息的目的地
    cms::Destination* destination;
    //	消息生产者
    cms::MessageProducer* producer;
    //	topic 或者 queue
    bool useTopic;
    //	ACK消息响应
    bool clientAck;
    //	消息连接URL
    std::string brokerURI;
    //	topic or queue 名称
    std::string destURI;
    //	发送锁
    decaf::util::concurrent::Mutex m_mutexOfSend;
private:

    ActivemqProducer( const ActivemqProducer& );
    ActivemqProducer& operator= ( const ActivemqProducer& );

public:

    ActivemqProducer( const std::string& brokerURI
                    ,const std::string& destURI
                    , bool useTopic = false
                    , bool clientAck = false );

    virtual ~ActivemqProducer();
    /*
		函数名：_Init
		形参：
			无
		功能：
			producer初始化
		返回值：
			正常返回RET_OK，异常返回RET_ERR
	*/
	int _Init();
	/*
		函数名：_SendMessage
		形参：
			[in]strMessage_		待发送的消息文本
		功能：消息生产者发送消息
		返回值：
			无
	*/
	void _SendBytesMessage(const std::string& strMessage_, int nDeliveryMode_=1, int nPriority_=0, long long llTimetoLive=10000);
	/*
		函数名：_SendTextMessage
		形参：
			[in]strMessage_		待发送的消息文本
		功能：消息生产者发送消息
		返回值：
			无
	*/
	void _SendTextMessage(const std::string& strMessage_, int nDeliveryMode_=1, int nPriority_=0, long long llTimetoLive=10000);
	/*
		函数名：_Close
		形参：
			无
		功能：对象关闭操作
		返回值：
			无
	*/
    void _Close();
private:
	/*
		函数名：_Cleanup
		形参：
			无
		功能：资源清理
		返回值：
			无
	*/
    void _Cleanup();
};

#endif	//	ACTIVEMQ_PRODUCER_H_


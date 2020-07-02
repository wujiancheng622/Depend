/*
	文件说明
	功能：		activemq接口说明
	作者：		华伟宏
	修改日志：	2016-08-13创建
*/
#ifndef _ACTIVEMQ_API_H
#define	_ACTIVEMQ_API_H

#include "ActivemqConsumer.h"
#include "ActivemqProducer.h"
#include <cms/BytesMessage.h>
#include <string>
#include "MqLog.h"
#include "ActivemqParseMessage.h"
#include "ActivemqThreadTaskFactory.h"

#define DEFUALT_TIME_TO_LIVE		10000
#define	DEFUALT_NON_PERSISTENT		1
#define	DEFAULT_PRIORITY			0

/*********************************************************************************************************
*	mq初始化工作，包括
*	1、hlog_init	2、_CreateMqLog		3、_InitMq	4、初始化mq线程池
*	反初始化工作包括
*	1、_UninitMq	2、hlog_uninit	
*	日志库采用log4cplus开源库，初始化和反初始化需要按实际情况进行
*********************************************************************************************************/
/*
	函数名：hlog_init
	形参：
		无
	功能：初始化日志库
	返回值：
		成功返回RET_OK，失败返回RET_ERR
	特别说明:
		mq库执行必须初始化日志库，否则会出错
*/
extern int hlog_init();
extern int hlog_uninit(void);
/*
	函数名：hlog_init
	形参：
		无
	功能：初始化日志库
	返回值：
		成功返回RET_OK，失败返回RET_ERR
	特别说明:
		mq库执行必须初始化日志库，否则会出错
*/
int _CreateMqLog();
/*
	函数名：_InitMq
	形参：
		无
	功能：activemq库初始化
	返回值：
		成功返回RET_OK，失败返回RET_ERR
*/
int _InitMq();
/*
	函数名：_UninitMq
	形参：
		无
	功能：activemq库反初始化
	返回值：
		无
*/
void _UninitMq();
/*********************************************************************************************************
*	mq线程池
*********************************************************************************************************/
/*
	函数名：InitThreadPoolByActivemq
	形参：
		[in]nCorePoolSize		
		[in]nMaxPoolSize			线程池最大线程数
		[in]llKeepAliveTime			线程生命期
	功能：
		activemq线程池初始化
	返回值：
		无
*/
int InitThreadPoolByActivemq(int nCorePoolSize,int nMaxPoolSize,long long llKeepAliveTime);
/*
	函数名：UninitThreadPoolByActivemq
	形参：
		无
	功能：
		activemq线程池反初始化
	返回值：
		无
*/
void UninitThreadPoolByActivemq();
/*
	函数名：ExcuteThreadByActivemq
	形参：
		[in]pFactory_	线程任务对象
	功能：
		执行线程任务
	返回值：
		成功返回RET_OK，失败返回RET_ERR
	特别说明:
		
*/
int ExcuteThreadByActivemq(ActivemqThreadTaskFactory* pFactory_);
/*********************************************************************************************************
*	消息消费者 --- ActivemqConsumer
*********************************************************************************************************/
/*
	函数名：_CreateActivemqConsumer
	形参：
		[in]brokerURI			连接URL
		[in]destURI				topic or queue 名称
		[in]userTopic			true=topic false=queue
		[in]clientAck			true=clientack
	功能：
		创建一个消息消费者
	返回值：
		正确返回ActivemqConsumer的对象指针，异常返回NULL
*/
ActivemqConsumer* _CreateActivemqConsumer(const std::string& brokerURI_,
                const std::string& destURI_,
                bool useTopic_=false,
                bool clientAck_=false);
/*
	函数名：_CloseActivemqConsumer
	形参：
		[in]pConsumer_			mq消息消费者
	功能：
	返回值：消息消费者者对象注销
		无
*/
void _CloseActivemqConsumer(ActivemqConsumer* pConsumer_);
/*
	函数名：_ParseMessageFromMq
	形参：
		[in]strMessage_				待处理的的消息字符串
	功能：
		用于解析mq消息和执行相关业务逻辑
	返回值：
		正常返回RET_OK，错误返回RET_ERR
	特别说明:
		该接口是 回调函数  ，需要使用者自己实现，我封装库这边会回调这个实现
*/
extern int _ParseMessageFromMq(std::string& strMessage_);

/*	
	功能:
		判断消费者监听是否存在
	返回值:
		存在返回true，不存在返回false
*/
bool IsExistListener(ActivemqConsumer* pConsumer_);
/*********************************************************************************************************
*	消息生产者 --- ActivemqProducer
*********************************************************************************************************/
/*
	函数名：_CreateActivemqProducer
	形参：
		[in]brokerURI			连接URL
		[in]destURI				topic or queue 名称
		[in]userTopic			true=topic false=queue
		[in]clientAck			true=clientack
	功能：
		创建一个消息生产者
	返回值：
		正确返回ActivemqConsumer的对象指针，异常返回NULL
*/
ActivemqProducer* _CreateActivemqProducer(const std::string& brokerURI_,
                const std::string& destURI_,
                bool useTopic_=false,
                bool clientAck_=false);
/*
	函数名：_CloseActivemqConsumer
	形参：
		[in]pProducer_			mq消息消费者
	功能：
	返回值：消息消费者者对象注销
		无
*/
void _CloseActivemqProducer(ActivemqProducer* pProducer_);

/*
	函数名：_SendBytesMessage
	形参：
		[in]pProducer_			消息生产者
		[in]strMessage_			待发送消息字符串(经过Protobuf序列化后的Protobuf对象字符串)
	功能：
	返回值：发送字符串消息
		无
*/
int _SendBytesMessage(ActivemqProducer* pProducer_, const std::string& strMessage_, int nDeliveryMode_=DEFUALT_NON_PERSISTENT, int nPriority_=DEFAULT_PRIORITY, long long llTimetoLive=DEFUALT_TIME_TO_LIVE);

/*
	函数名：_SendTextMessage
	形参：
		[in]pProducer_			消息生产者
		[in]strMessage_			待发送消息字符串(经过Protobuf序列化后的Protobuf对象字符串)
	功能：
	返回值：发送字符串消息
		无
*/
int _SendTextMessage(ActivemqProducer* pProducer_, const std::string& strMessage_, int nDeliveryMode_=DEFUALT_NON_PERSISTENT, int nPriority_=DEFAULT_PRIORITY, long long llTimetoLive=DEFUALT_TIME_TO_LIVE);

#endif	//	_ACTIVEMQ_API_H
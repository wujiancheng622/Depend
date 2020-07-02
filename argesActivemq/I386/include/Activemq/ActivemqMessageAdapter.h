/*
	文件说明
	功能：		activemq消息适配器定义；根据消息类型和消息体请求类型调用不用命令
	作者：		华伟宏
	修改日志：	2016-07-21创建
*/

#ifndef ACTIVEMQ_MESSAGE_ADAPTER_H_
#define	ACTIVEMQ_MESSAGE_ADAPTER_H_

#include <cms/MessageProducer.h>
#include <cms/Session.h>
#include <cms/BytesMessage.h>
#include "ActivemqConsumer.h"


class ActivemqMessageAdapter
{
private:
    ActivemqMessageAdapter(const ActivemqMessageAdapter&);
    ActivemqMessageAdapter& operator=(const ActivemqMessageAdapter&);

public:
    ActivemqMessageAdapter(){}
	~ActivemqMessageAdapter()
	{
		_Close();
	}

	ActivemqMessageAdapter(ActivemqConsumer* pConsumer_);

private:
	ActivemqConsumer*		m_pConsumer;
	
public:
	/*
		函数名：_AdpterMessage
		形参：
			[in]strMessage_				待处理的消息字符串
			[in]_ParseMessage			消息处理的回调函数指针
		功能：
			消息适配处理
		返回值：
			成功返回RET_OK，失败返回RET_ERR
	*/
	int _AdpterMessage(std::string& strMessage_, int (*_ParseMessage)(std::string& strMessage_));

	int _Init();
	void _Close();
	void _CleanUp();
};

#endif	//	ACTIVEMQ_MESSAGE_ADAPTER_H_
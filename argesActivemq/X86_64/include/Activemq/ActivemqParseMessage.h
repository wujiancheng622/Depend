/*
	文件说明
	功能：		Consumer的接收消息解析和执行接口定义
	作者：		华伟宏
	修改日志：	2016-08-13创建
*/
#ifndef _ACTIVEMQ_PARSE_MESSAGE_H_
#define _ACTIVEMQ_PARSE_MESSAGE_H_

#include <string>
#include <cms/BytesMessage.h>
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
int _ParseMessageFromMq(std::string& strMessage_);

#endif	//	_ACTIVEMQ_PARSE_MESSAGE_H_
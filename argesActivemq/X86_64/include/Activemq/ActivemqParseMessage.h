/*
	�ļ�˵��
	���ܣ�		Consumer�Ľ�����Ϣ������ִ�нӿڶ���
	���ߣ�		��ΰ��
	�޸���־��	2016-08-13����
*/
#ifndef _ACTIVEMQ_PARSE_MESSAGE_H_
#define _ACTIVEMQ_PARSE_MESSAGE_H_

#include <string>
#include <cms/BytesMessage.h>
/*
	��������_ParseMessageFromMq
	�βΣ�
		[in]strMessage_				������ĵ���Ϣ�ַ���
	���ܣ�
		���ڽ���mq��Ϣ��ִ�����ҵ���߼�
	����ֵ��
		��������RET_OK�����󷵻�RET_ERR
	�ر�˵��:
		�ýӿ��� �ص�����  ����Ҫʹ�����Լ�ʵ�֣��ҷ�װ����߻�ص����ʵ��
*/
int _ParseMessageFromMq(std::string& strMessage_);

#endif	//	_ACTIVEMQ_PARSE_MESSAGE_H_
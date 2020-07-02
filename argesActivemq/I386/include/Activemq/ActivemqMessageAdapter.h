/*
	�ļ�˵��
	���ܣ�		activemq��Ϣ���������壻������Ϣ���ͺ���Ϣ���������͵��ò�������
	���ߣ�		��ΰ��
	�޸���־��	2016-07-21����
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
		��������_AdpterMessage
		�βΣ�
			[in]strMessage_				���������Ϣ�ַ���
			[in]_ParseMessage			��Ϣ����Ļص�����ָ��
		���ܣ�
			��Ϣ���䴦��
		����ֵ��
			�ɹ�����RET_OK��ʧ�ܷ���RET_ERR
	*/
	int _AdpterMessage(std::string& strMessage_, int (*_ParseMessage)(std::string& strMessage_));

	int _Init();
	void _Close();
	void _CleanUp();
};

#endif	//	ACTIVEMQ_MESSAGE_ADAPTER_H_
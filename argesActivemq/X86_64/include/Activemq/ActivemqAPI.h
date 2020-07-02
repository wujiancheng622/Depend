/*
	�ļ�˵��
	���ܣ�		activemq�ӿ�˵��
	���ߣ�		��ΰ��
	�޸���־��	2016-08-13����
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
*	mq��ʼ������������
*	1��hlog_init	2��_CreateMqLog		3��_InitMq	4����ʼ��mq�̳߳�
*	����ʼ����������
*	1��_UninitMq	2��hlog_uninit	
*	��־�����log4cplus��Դ�⣬��ʼ���ͷ���ʼ����Ҫ��ʵ���������
*********************************************************************************************************/
/*
	��������hlog_init
	�βΣ�
		��
	���ܣ���ʼ����־��
	����ֵ��
		�ɹ�����RET_OK��ʧ�ܷ���RET_ERR
	�ر�˵��:
		mq��ִ�б����ʼ����־�⣬��������
*/
extern int hlog_init();
extern int hlog_uninit(void);
/*
	��������hlog_init
	�βΣ�
		��
	���ܣ���ʼ����־��
	����ֵ��
		�ɹ�����RET_OK��ʧ�ܷ���RET_ERR
	�ر�˵��:
		mq��ִ�б����ʼ����־�⣬��������
*/
int _CreateMqLog();
/*
	��������_InitMq
	�βΣ�
		��
	���ܣ�activemq���ʼ��
	����ֵ��
		�ɹ�����RET_OK��ʧ�ܷ���RET_ERR
*/
int _InitMq();
/*
	��������_UninitMq
	�βΣ�
		��
	���ܣ�activemq�ⷴ��ʼ��
	����ֵ��
		��
*/
void _UninitMq();
/*********************************************************************************************************
*	mq�̳߳�
*********************************************************************************************************/
/*
	��������InitThreadPoolByActivemq
	�βΣ�
		[in]nCorePoolSize		
		[in]nMaxPoolSize			�̳߳�����߳���
		[in]llKeepAliveTime			�߳�������
	���ܣ�
		activemq�̳߳س�ʼ��
	����ֵ��
		��
*/
int InitThreadPoolByActivemq(int nCorePoolSize,int nMaxPoolSize,long long llKeepAliveTime);
/*
	��������UninitThreadPoolByActivemq
	�βΣ�
		��
	���ܣ�
		activemq�̳߳ط���ʼ��
	����ֵ��
		��
*/
void UninitThreadPoolByActivemq();
/*
	��������ExcuteThreadByActivemq
	�βΣ�
		[in]pFactory_	�߳��������
	���ܣ�
		ִ���߳�����
	����ֵ��
		�ɹ�����RET_OK��ʧ�ܷ���RET_ERR
	�ر�˵��:
		
*/
int ExcuteThreadByActivemq(ActivemqThreadTaskFactory* pFactory_);
/*********************************************************************************************************
*	��Ϣ������ --- ActivemqConsumer
*********************************************************************************************************/
/*
	��������_CreateActivemqConsumer
	�βΣ�
		[in]brokerURI			����URL
		[in]destURI				topic or queue ����
		[in]userTopic			true=topic false=queue
		[in]clientAck			true=clientack
	���ܣ�
		����һ����Ϣ������
	����ֵ��
		��ȷ����ActivemqConsumer�Ķ���ָ�룬�쳣����NULL
*/
ActivemqConsumer* _CreateActivemqConsumer(const std::string& brokerURI_,
                const std::string& destURI_,
                bool useTopic_=false,
                bool clientAck_=false);
/*
	��������_CloseActivemqConsumer
	�βΣ�
		[in]pConsumer_			mq��Ϣ������
	���ܣ�
	����ֵ����Ϣ�������߶���ע��
		��
*/
void _CloseActivemqConsumer(ActivemqConsumer* pConsumer_);
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
extern int _ParseMessageFromMq(std::string& strMessage_);

/*	
	����:
		�ж������߼����Ƿ����
	����ֵ:
		���ڷ���true�������ڷ���false
*/
bool IsExistListener(ActivemqConsumer* pConsumer_);
/*********************************************************************************************************
*	��Ϣ������ --- ActivemqProducer
*********************************************************************************************************/
/*
	��������_CreateActivemqProducer
	�βΣ�
		[in]brokerURI			����URL
		[in]destURI				topic or queue ����
		[in]userTopic			true=topic false=queue
		[in]clientAck			true=clientack
	���ܣ�
		����һ����Ϣ������
	����ֵ��
		��ȷ����ActivemqConsumer�Ķ���ָ�룬�쳣����NULL
*/
ActivemqProducer* _CreateActivemqProducer(const std::string& brokerURI_,
                const std::string& destURI_,
                bool useTopic_=false,
                bool clientAck_=false);
/*
	��������_CloseActivemqConsumer
	�βΣ�
		[in]pProducer_			mq��Ϣ������
	���ܣ�
	����ֵ����Ϣ�������߶���ע��
		��
*/
void _CloseActivemqProducer(ActivemqProducer* pProducer_);

/*
	��������_SendBytesMessage
	�βΣ�
		[in]pProducer_			��Ϣ������
		[in]strMessage_			��������Ϣ�ַ���(����Protobuf���л����Protobuf�����ַ���)
	���ܣ�
	����ֵ�������ַ�����Ϣ
		��
*/
int _SendBytesMessage(ActivemqProducer* pProducer_, const std::string& strMessage_, int nDeliveryMode_=DEFUALT_NON_PERSISTENT, int nPriority_=DEFAULT_PRIORITY, long long llTimetoLive=DEFUALT_TIME_TO_LIVE);

/*
	��������_SendTextMessage
	�βΣ�
		[in]pProducer_			��Ϣ������
		[in]strMessage_			��������Ϣ�ַ���(����Protobuf���л����Protobuf�����ַ���)
	���ܣ�
	����ֵ�������ַ�����Ϣ
		��
*/
int _SendTextMessage(ActivemqProducer* pProducer_, const std::string& strMessage_, int nDeliveryMode_=DEFUALT_NON_PERSISTENT, int nPriority_=DEFAULT_PRIORITY, long long llTimetoLive=DEFUALT_TIME_TO_LIVE);

#endif	//	_ACTIVEMQ_API_H
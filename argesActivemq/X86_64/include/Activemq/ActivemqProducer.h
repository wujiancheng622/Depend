/*
	�ļ�˵��
	���ܣ�		activemq����Ϣ�����߶���
	���ߣ�		��ΰ��
	�޸���־��	2016-07-21����
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
	//	����
    cms::Connection* connection;
    //	���ӻỰ
    cms::Session* session;
    //	��Ϣ��Ŀ�ĵ�
    cms::Destination* destination;
    //	��Ϣ������
    cms::MessageProducer* producer;
    //	topic ���� queue
    bool useTopic;
    //	ACK��Ϣ��Ӧ
    bool clientAck;
    //	��Ϣ����URL
    std::string brokerURI;
    //	topic or queue ����
    std::string destURI;
    //	������
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
		��������_Init
		�βΣ�
			��
		���ܣ�
			producer��ʼ��
		����ֵ��
			��������RET_OK���쳣����RET_ERR
	*/
	int _Init();
	/*
		��������_SendMessage
		�βΣ�
			[in]strMessage_		�����͵���Ϣ�ı�
		���ܣ���Ϣ�����߷�����Ϣ
		����ֵ��
			��
	*/
	void _SendBytesMessage(const std::string& strMessage_, int nDeliveryMode_=1, int nPriority_=0, long long llTimetoLive=10000);
	/*
		��������_SendTextMessage
		�βΣ�
			[in]strMessage_		�����͵���Ϣ�ı�
		���ܣ���Ϣ�����߷�����Ϣ
		����ֵ��
			��
	*/
	void _SendTextMessage(const std::string& strMessage_, int nDeliveryMode_=1, int nPriority_=0, long long llTimetoLive=10000);
	/*
		��������_Close
		�βΣ�
			��
		���ܣ�����رղ���
		����ֵ��
			��
	*/
    void _Close();
private:
	/*
		��������_Cleanup
		�βΣ�
			��
		���ܣ���Դ����
		����ֵ��
			��
	*/
    void _Cleanup();
};

#endif	//	ACTIVEMQ_PRODUCER_H_


/*
	�ļ�˵��
	���ܣ�		activemq��Ϣ������ʵ��
	���ߣ�		��ΰ��
	�޸���־��	2016-07-21����
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
	//	����
    cms::Connection* 			connection;
	//	���ӻỰ
	cms::Session*				session;
private:
	
	//	������Ϣ��Ŀ�ĵ�
    cms::Destination* 			m_pRequestDestination;
	//	��Ϣ������
    cms::MessageConsumer* 		consumer;
	//	��������
    bool 						useTopic;
	//	��Ϣ����URL
    std::string 				brokerURI;
	//	��Ϣ��������
    std::string 				destURI;
	//	ACK
    bool 						clientAck;
	//	��ǰ������	
	long 						numOfMessagingTasks;
	//	�߳���
	decaf::util::concurrent::Mutex 	mutexGeneral;
	//	�߳���
	decaf::util::concurrent::Mutex 	m_mutexMessage;
	//	��Ϣ����ʱ�� ms
	int							m_nAliveTime;
	//	ֹͣ��Ϣ�����׼
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
		��������_Init
		�βΣ�
			��
		���ܣ�
			consumer��ʼ��
		����ֵ��
			�ɹ�����RET_OK��ʧ�ܷ���RET_ERR
	*/
    int _Init();
	/*
		��������Close
		�βΣ�
			��
		���ܣ�����رմ���
		����ֵ��
			��
	*/
    void _Close();
	
	/*
		��������isMessageExpired
		�βΣ�
			[in]message		��Ϣ����
		���ܣ�
			�ж���Ϣ�Ƿ����
		����ֵ��
			���ڷ���true�����򷵻�false
	*/
	bool _IsMessageExpired(const cms::Message* message_);
	/*
		��������IncreaseNumOfMessagingTasks
		�βΣ�
			��
		���ܣ�
			��Ϣ������������
		����ֵ��
			��
	*/
	void _IncreaseNumOfMessagingTasks();
	/*
		��������_DecreaseNumOfMessagingTasks
		�βΣ�
			��
		���ܣ�
			��Ϣ��������-1
		����ֵ��
			��
	*/
	void _DecreaseNumOfMessagingTasks();
	/*
		��������_GetNumOfMessagingTasks
		�βΣ�
			��
		���ܣ�
			��ȡ��ǰ��Ϣ���������
		����ֵ��
			���ڴ���ʹ��������������
	*/
	long _GetNumOfMessagingTasks();
	/*
		��������_RunConsumer
		�βΣ�
			��
		���ܣ�
			consumer���úͳ�ʼ��
		����ֵ��
			��
	*/
    int runConsumer();
	/*
		��������_QueueMessagingTask
		�βΣ�
			[in]strMessage_				���������Ϣ�ַ���
		���ܣ�
			��Ϣ�������
		����ֵ��
			��
	*/
	int _QueueMessagingTask(const unsigned char* _pMassage, const int _nLen);
	/*
		��������_OnMessage
		�βΣ�
			[in]message_	���������Ϣ�ı�
		���ܣ�
			consumer������Ϣ����
		����ֵ��
			��
	*/
    virtual void onMessage(const cms::Message* message_);

	/*
		��������run
		�βΣ�
			��
		���ܣ���Ӧ��Ϣ���ü���ʼ������
		����ֵ��
			��
	*/
	virtual void run();
	/*
		��������_AdpterMessage
		�βΣ�
			[in]strMessage_				���������Ϣ�ַ���
		���ܣ�������Ϣ����
		����ֵ��
			�ɹ�����RET_OK��ʧ�ܷ���RET_ERR
	*/
	int _AdpterMessage(std::string& strMessage_);
	/*
		��������_ExecuteMessagingTask
		�βΣ�
			[in]strMessage_				���������Ϣ�ַ���
		���ܣ�
			ִ����Ϣ����
		����ֵ��
			�ɹ�����RET_OK��ʧ�ܷ���RET_ERR
	*/
	int _ExecuteMessagingTask(std::string& strMessage_);

	/*
		����:
			�ж������߼����Ƿ����
		����ֵ:
			���ڷ���true�������ڷ���false
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
		��������_Cleanup
		�βΣ�
			��
		���ܣ�
			��Դ����
		����ֵ��
			��
	*/
    void _Cleanup();
};

#endif	//	ACTIVEMQ_CONSUMER_H_


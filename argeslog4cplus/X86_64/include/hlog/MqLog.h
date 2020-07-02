#ifndef _MQ_LOG_H_
#define _MQ_LOG_H_

#include "hlog.h"

//	��־·�����ļ���
#define	MQ_LOG_INSTANCE		"./log/mq.log"

#define CREATE_MQ_LOG()								\
do													\
{													\
	if(_CreateLogInstance(MQ_LOG_INSTANCE) != RET_OK)			\
	{												\
		printf("ʵ����mq��־����ʧ��!\n");			\
		return RET_ERR;								\
	}												\
	printf("ʵ����Mq��־����ɹ�!\n");				\
}while(0);

#if defined(WIN32)||defined(WIN64)||defined(WINCE)		//	Windowsʹ��
#define  MQ_LOG_ERROR(format,...) 								\
do{																		\
		char message[LOG_BUFF_SIZE] = {0};								\
		sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
		message[LOG_BUFF_SIZE-1] = '\0';								\
		LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
		printf("%s\t %s\t %d\tERROR %s\n", __FILE__, __FUNCTION__, __LINE__, message);	\
}while(0);
			
#define  MQ_LOG_INFO(format,...) 									\
do{																		\
		char message[LOG_BUFF_SIZE] = {0};								\
		sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
		message[LOG_BUFF_SIZE-1] = '\0';								\
		LOG4CPLUS_INFO(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
		printf("%s\t %s\t %d\tINFO %s\n", __FILE__, __FUNCTION__, __LINE__, message);		\
}while(0);

#define  MQ_LOG_DEBUG(format,...) 								\
do{																		\
		char message[LOG_BUFF_SIZE] = {0};								\
		sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
		message[LOG_BUFF_SIZE-1] = '\0';								\
		LOG4CPLUS_DEBUG(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
		printf("%s\t %s\t %d\tDEBUG %s\n", __FILE__, __FUNCTION__, __LINE__, message);	\
}while(0);

#define  MQ_LOG_WARN(format,...) 									\
do{																		\
		char message[LOG_BUFF_SIZE] = {0};								\
		sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);			\
		message[LOG_BUFF_SIZE-1] = '\0';								\
		LOG4CPLUS_WARN(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
		printf("%s\t %s\t %d\tWARN %s\n", __FILE__, __FUNCTION__, __LINE__, message);		\
}while(0);

#define  MQ_PARAME_ASSERT(condition, format, ...) 				\
do{																		\
		if(condition)													\
		{																\
			char message[LOG_BUFF_SIZE] = {0};							\
			sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);		\
			message[LOG_BUFF_SIZE-1] = '\0';							\
			LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
			printf("%s\t %s\t %d\tERROR %s\n", __FILE__, __FUNCTION__, __LINE__, message);		\
			return;														\
		}																\
}while(0);

#define  MQ_PARAME_ASSERT_INT(condition,format,...) 				\
do{																		\
		if(condition)													\
		{																\
			char message[LOG_BUFF_SIZE] = {0};							\
			sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);		\
			message[LOG_BUFF_SIZE-1] = '\0';							\
			LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
			printf("%s\t %s\t %d\tERROR %s\n", __FILE__, __FUNCTION__, __LINE__, message);		\
			return -1;													\
		}																\
}while(0);

#define  MQ_PARAME_ASSERT_BOOL(condition,format,...) 				\
do{																		\
		if(condition)													\
		{																\
			char message[LOG_BUFF_SIZE] = {0};							\
			sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);		\
			message[LOG_BUFF_SIZE-1] = '\0';							\
			LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
			printf("%s\t %s\t %d\tERROR %s\n", __FILE__, __FUNCTION__, __LINE__, message);		\
			return false;												\
		}																\
}while(0);

#define  MQ_PARAME_ASSERT_POINTER(condition, format, ...) 		\
do{																		\
		if(condition)													\
		{																\
			char message[LOG_BUFF_SIZE] = {0};							\
			sprintf_s(message, LOG_BUFF_SIZE, format, __VA_ARGS__);		\
			message[LOG_BUFF_SIZE-1] = '\0';							\
			LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
			printf("%s\t %s\t %d\tERROR %s\n", __FILE__, __FUNCTION__, __LINE__, message);		\
			return NULL;												\
		}																\
}while(0);

#else	//	Linuxʹ��

#define  MQ_LOG_ERROR(format,args...) 							\
do{																		\
		char message[LOG_BUFF_SIZE] = {0};								\
		snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
		message[LOG_BUFF_SIZE-1] = '\0';								\
		LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
		printf("%s\t %s\t %d\tERROR %s\n", __FILE__, __FUNCTION__, __LINE__, message);			\
}while(0);
			
#define  MQ_LOG_INFO(format,args...) 								\
do{																		\
		char message[LOG_BUFF_SIZE] = {0};								\
		snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
		message[LOG_BUFF_SIZE-1] = '\0';								\
		LOG4CPLUS_INFO(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
		printf("%s\t %s\t %d\tINFO %s\n", __FILE__, __FUNCTION__, __LINE__, message);				\
}while(0);

#define  MQ_LOG_DEBUG(format,args...) 							\
do{																		\
		char message[LOG_BUFF_SIZE] = {0};								\
		snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
		message[LOG_BUFF_SIZE-1] = '\0';								\
		LOG4CPLUS_DEBUG(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
		printf("%s\t %s\t %d\tDEBUG %s\n", __FILE__, __FUNCTION__, __LINE__, message);			\
}while(0);

#define  MQ_LOG_WARN(format,args...) 								\
do{																		\
		char message[LOG_BUFF_SIZE] = {0};								\
		snprintf(message, LOG_BUFF_SIZE, format, ##args);				\
		message[LOG_BUFF_SIZE-1] = '\0';								\
		LOG4CPLUS_WARN(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
		printf("%s\t %s\t %d\tWARN %s\n", __FILE__, __FUNCTION__, __LINE__, message);				\
}while(0);

#define  MQ_PARAME_ASSERT(condition, format, args...) 			\
do{																		\
		if(condition)													\
		{																\
			char message[LOG_BUFF_SIZE] = {0};							\
			snprintf(message, LOG_BUFF_SIZE, format, ##args);			\
			message[LOG_BUFF_SIZE-1] = '\0';							\
			LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
			printf("%s\t %s\t %d\tERROR %s\n", __FILE__, __FUNCTION__, __LINE__, message);		\
			return;														\
		}																\
}while(0);

#define  MQ_PARAME_ASSERT_INT(condition, format, args...) 		\
do{																		\
		if(condition)													\
		{																\
			char message[LOG_BUFF_SIZE] = {0};							\
			snprintf(message, LOG_BUFF_SIZE, format, ##args);			\
			message[LOG_BUFF_SIZE-1] = '\0';							\
			LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
			printf("%s\t %s\t %d\tERROR %s\n", __FILE__, __FUNCTION__, __LINE__, message);		\
			return -1;													\
		}																\
}while(0);

#define MQ_PARAME_ASSERT_BOOL(condition, format, args...) 		\
do{																		\
		if(condition)													\
		{																\
			char message[LOG_BUFF_SIZE] = {0};							\
			snprintf(message, LOG_BUFF_SIZE, format, ##args);			\
			message[LOG_BUFF_SIZE-1] = '\0';							\
			LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
			printf("%s\t %s\t %d\tERROR %s\n", __FILE__, __FUNCTION__, __LINE__, message);		\
			return false;												\
		}																\
}while(0);

#define  MQ_PARAME_ASSERT_POINTER(condition, format, args...) 	\
do{																		\
		if(condition)													\
		{																\
			char message[LOG_BUFF_SIZE] = {0};							\
			snprintf(message, LOG_BUFF_SIZE, format, ##args);			\
			message[LOG_BUFF_SIZE-1] = '\0';							\
			LOG4CPLUS_ERROR(log4cplus::Logger::getInstance(LOG4CPLUS_TEXT(MQ_LOG_INSTANCE)), message);		\
			printf("%s\t %s\t %d\tERROR %s\n", __FILE__, __FUNCTION__, __LINE__, message);		\
			return NULL;												\
		}																\
}while(0);

#endif	//	linux

#endif	//	_MQ_LOG_H_


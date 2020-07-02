/*
	�ļ�˵��
	���ܣ�		log4cxx���ⲿ���ýӿ�
	���ߣ�		��ΰ��
	�޸���־��	2015-12-02
*/
#ifndef _LOG4CXX_HLOG_H
#define _LOG4CXX_HLOG_H

#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#define LOG_BUFF_SIZE	1024
#define MAX_SIZE_OF_LOG_FILE		1048576000			//	��־�ļ����1G
#define MAX_NUM_OF_LOG_BACK_UP	25				//	����25����־�ļ�

typedef enum
{
	RET_ERR = -1,
	RET_OK  = 0,
}RET_ENUM;

int hlog_init();
int hlog_uninit(void);
int _CreateLogInstance(const char* szLogName_);

#endif
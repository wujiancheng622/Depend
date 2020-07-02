#ifndef _MQ_DEFILE_H_
#define _MQ_DEFILE_H_

typedef enum
{
	EQUAL_VALUE = 0,
}COMPARE_ENUM;

typedef enum
{
	IS_RESPONSE = 0,
	NO_RESPONSE = 1,
}ISRESPONSE_ENUM;

typedef enum
{
	BYTESMESSAGE = 1,
	TEXTMESSAGE = 2
}MQ_MESSAGE_TYPE_ENUM;

//	URL最大长度
#define	URL_MAX_LEN						1024
#define	MQ_MAX_LEN						(1024*10)	


//	TextMessage
#define TEXT_MESSAGE	"TextMessage"
//	BytesMessage
#define BYTES_MESSAGE	"BytesMessage"



#endif	//	_MQ_DEFILE_H_


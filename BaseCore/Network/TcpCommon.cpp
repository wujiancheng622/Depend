#include "TcpCommon.h"
#include <string.h>

//const char *PACKET_HEADER="TIANSHITONG_DATA_BEGIN(";//TIANSHITONG_DATA_BEGIN  BOOST_ASIO_DATA_BEGIN
//const char *PACKET_TRAILER=")TIANSHITONG_DATA_END";//TIANSHITONG_DATA_END  BOOST_ASIO_DATA_END
//const int PACKET_HEADER_LEN=strlen(PACKET_HEADER); 
//const int PACKET_TRAILER_LEN=strlen(PACKET_TRAILER); 

const int MAX_RECV_BYTES_ONE_TIME=40960; 


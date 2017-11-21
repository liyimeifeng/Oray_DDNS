// PHGlobal.h: interface for the CBaseThread class.
//
//////////////////////////////////////////////////////////////////////
/*! \file PHGlobal.h
*  \author skyvense
*  \date   2009-09-14
*  \brief PHDDNS �ͻ���ʵ��	
*/

#ifndef __PHGLOBAL__H__
#define __PHGLOBAL__H__
#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
//#include <sys/timeb.h>
#endif

#ifdef WIN32
#define sleep(x) Sleep(x*1000)
#else
#define INVALID_SOCKET (-1)
#define MAX_PATH	260
#endif

#include "phsocket.h"
#include "pherr.h"

#define MAX_TCP_PACKET_LEN	8192

//! TCPָ���
#ifdef OFFICIAL_CLIENT
	#define COMMAND_AUTH	"auth phsrv6\r\n"
#else
	#define COMMAND_AUTH	"auth router6\r\n"
#endif

#define COMMAND_REGI    "regi a"
#define COMMAND_CNFM    "cnfm\r\n"
#define COMMAND_STAT_USER    "stat user\r\n"
#define COMMAND_STAT_DOM     "stat domain\r\n"
#define COMMAND_QUIT    "quit\r\n"

//! ����������ָ��
#define UDP_OPCODE_UPDATE_VER2		0x2010
//! ��������������������
#define UDP_OPCODE_UPDATE_OK		0x2050
//! ���������������ش���
#define UDP_OPCODE_UPDATE_ERROR		1000

//! ������ע����¼
#define UDP_OPCODE_LOGOUT			11

//! ���������ܲ��ִ�С
#define KEEPALIVE_PACKET_LEN	20


//! ת��״̬�뵽�ı���
const char *convert_status_code(int nCode);

//! ת��IP��ַ���ı���
const char *my_inet_ntoa(int ip);
void reverse_byte_order(int *in_array,int arraysize);
//! �������ṹ
typedef struct  
{
	//! �Ի�ID
	int lChatID;
	//! ������
	int lOpCode;
	//! ��ID
	int lID;
	//! У���
	int lSum;
	//! ������
	int lReserved;
}DATA_KEEPALIVE;

//! ���°���չ�ṹ�����ڷ���������ʱIP��ַ
typedef struct 
{
	DATA_KEEPALIVE keepalive;
	int ip;
}DATA_KEEPALIVE_EXT;

typedef struct __PHGlobal PHGlobal;

	typedef void (*CALLBACK_OnStatusChanged)(PHGlobal*, int status, int data); 
	//! �˺����õ�״̬���
	/*! status���ܵ�ֵ��
		enum MessageCodes
		{
			okConnected = 0,
			okAuthpassed,
			okDomainListed,
			okDomainsRegistered,
			okKeepAliveRecved,
			okConnecting,
			okRetrievingMisc,
			okRedirecting,
		
		  errorConnectFailed = 0x100,
		  errorSocketInitialFailed,
		  errorAuthFailed,
		  errorDomainListFailed,
		  errorDomainRegisterFailed,
		  errorUpdateTimeout,
		  errorKeepAliveError,
		  errorRetrying,
		  errorAuthBusy,
		  errorStatDetailInfoFailed,

		  okNormal = 0x120,
		  okNoData,
		  okServerER,
		  errorOccupyReconnect,
		};
		���У�
		1����statusΪokDomainsRegisteredʱ��data�����û�����0(���),1(רҵ),2(��ҵ)
		2����statusΪokKeepAliveRecvedʱ��data���ؿͻ���IP��ַ��������ʽ��
		3����������£�dataһֱΪ0
	*/
	//! �˺����õ�ע���������ÿ��������ִ��һ��
	typedef void (*CALLBACK_OnDomainRegistered)(PHGlobal*, char *domainName); 
	//! �˺����õ��û���Ϣ��XML��ʽ
	typedef void (*CALLBACK_OnUserInfo)(PHGlobal*, char *userInfo, int length); 
	//! �˺����õ��û�������Ϣ��XML��ʽ
	typedef void (*CALLBACK_OnAccountDomainInfo)(PHGlobal*, char *domainInfo, int length); 


//! ȫ�ֱ���
struct __PHGlobal {
//basic system info
	//! Ƕ��ʽ�ͻ�����Ϣ��4λ�ͻ���ID + 4λ�汾��
	int clientinfo;
	//! Ƕ��ʽ��֤��
	int challengekey;

	//! ��������ַ
	char szHost[256];
	//! �������˿ڣ�6060�̶�
	short nPort;
	//! �û��˺���
	char szUserID[256];
	//! �û���������
	char szUserPWD[256];
	//! ���ذ󶨵�ַ��Ĭ����գ����ڶ������ʱָ������
	char szBindAddress[256];
//run-time controll variables
	//! �û�����
	int nUserType;
	BOOL bTcpUpdateSuccessed;
	char szChallenge[256];
	int nChallengeLen;
	int nChatID,nStartID,nLastResponseID;
	int tmLastResponse;
	int nAddressIndex;
	char szTcpConnectAddress[32];

	int cLastResult;
	int ip;

	int uptime;
	int lasttcptime;

	char szActiveDomains[255][255];

	//! ��ǰ�Ƿ���Ҫ����TCP����
	BOOL bNeed_connect;
	//! ���һ�η�����������ʱ��	
	int tmLastSend;

	int m_tcpsocket,m_udpsocket;
	BOOL bBigEndian;

  // ��ָ�룬 ����c++���������¼�֪ͨ
  void* user_data;

	CALLBACK_OnStatusChanged cbOnStatusChanged;
	CALLBACK_OnDomainRegistered cbOnDomainRegistered;
	CALLBACK_OnUserInfo cbOnUserInfo;
	CALLBACK_OnAccountDomainInfo cbOnAccountDomainInfo;
};

void init_global(PHGlobal *global);
void set_default_callback(PHGlobal *global);

#endif

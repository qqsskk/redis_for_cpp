#ifndef __REDIS_HANDLER_H__
#define __REDIS_HANDLER_H__

//#include "hiredis\hiredis.h" 
#include <hiredis/hiredis.h>
#include <string>

using namespace std;

enum
{
	M_REDIS_OK = 0, //ִ�гɹ�
	M_CONNECT_FAIL = -1, //����redisʧ��
	M_CONTEXT_ERROR = -2, //RedisContext���ش���
	M_REPLY_ERROR = -3, //redisReply����
	M_EXE_COMMAND_ERROR = -4 //redis����ִ�д���
};


class RedisHandler
{
public:
	RedisHandler();
	~RedisHandler();
	int connect(const string &addr, int port, const string &pwd = ""); //����redis���ݿ⣺addr��IP��ַ��port���˿ںţ�pwd������(Ĭ��Ϊ��)
	int disConnect(); //�Ͽ�����

	int setValue(const string &key, const string &value); //��ӻ��޸ļ�ֵ�ԣ��ɹ�����0��ʧ��<0
	int getValue(const string &key, string &value); //��ȡ����Ӧ��ֵ���ɹ�����0��ʧ��<0
	int delKey(const string &key); //ɾ�������ɹ�����Ӱ���������ʧ��<0
	int printAll(); //��ӡ���еļ�ֵ��

	string getErrorMsg(); //��ȡ������Ϣ
private:
	string m_addr; //IP��ַ
	int m_port; //�˿ں�
	string m_pwd; //����
	redisContext* pm_rct; //redis�ṹ��
	redisReply* pm_rr; //���ؽṹ��
	string error_msg; //������Ϣ

	int connectAuth(const string &pwd); //ʹ�������¼
	int handleReply(void* value = NULL, redisReply ***array = NULL); //�����صĽ��
};


#endif
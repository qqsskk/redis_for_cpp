#include "redis_handler.h"
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

RedisHandler::RedisHandler()
{
	m_addr = "";
	m_port = 0;
	m_pwd = "";
	pm_rct = NULL;
	pm_rr = NULL;
	error_msg = "";
}

RedisHandler::~RedisHandler()
{
	disConnect();
	pm_rct = NULL;
	pm_rr = NULL;
}

/*
����redis���ݿ�
addr: ��ַ��port���˿ںţ�pwd������
�ɹ�����M_REDIS_OK��ʧ�ܷ���M_CONNECT_FAIL
*/
int RedisHandler::connect(const string &addr = "127.0.0.1", int port = 6379, const string &pwd) {
	m_addr = addr;
	m_port = port;
	m_pwd = pwd;

	pm_rct = redisConnect(m_addr.c_str(), m_port);

	if (pm_rct->err)
	{
		error_msg = pm_rct->errstr;
		return M_CONNECT_FAIL;
	}

	if (!m_pwd.empty())
	{
		return connectAuth(m_pwd);
	}

	return M_REDIS_OK;
}

/*
�Ͽ�redis����
*/
int RedisHandler::disConnect()
{
	redisFree(pm_rct);
	freeReplyObject(pm_rr);
}

/*
��ӻ�����ֵ��
key������value��ֵ
�ɹ�����M_REDIS_OK��ʧ�ܷ���<0
*/
int RedisHandler::setValue(const string &key, const string &value)
{
	string cmd = "set " + key + " " + value;

	pm_rr = (redisReply*)redisCommand(pm_rct, cmd.c_str());

	return handleReply();
}

/*
��ȡ����Ӧ��ֵ
key������value��ֵ����
�ɹ�����M_REDIS_OK��ʧ�ܷ���<0
*/
int RedisHandler::getValue(const string &key, string &value)
{
	string cmd = "get " + key;

	pm_rr = (redisReply*)redisCommand(pm_rct, cmd.c_str());

	int ret = handleReply(&value);
}

/*
ɾ����
key����
�ɹ�����Ӱ�������������Ϊ0����ʧ�ܷ���<0
*/
int RedisHandler::delKey(const string &key)
{
	string cmd = "del " + key;

	pm_rr = (redisReply*)redisCommand(pm_rct, cmd.c_str());

	int rows = 0;
	int ret = handleReply(&rows);
	if (ret == M_REDIS_OK)
		return rows;
	else
		return ret;
}

/*
��ӡ���м�ֵ�Ե���Ļ��
*/
int RedisHandler::printAll()
{
	string cmd = "keys *";

	pm_rr = (redisReply*)redisCommand(pm_rct, cmd.c_str());

	int len ;
	redisReply **array;
	int ret = handleReply(&len, &array);
	if (ret == M_REDIS_OK)
	{
		for (int i = 0; i < len; i++)
			cout << string(array[i]->str) << endl;
	}
	else
		return 0;
}

/*
���ش�����Ϣ
*/
string RedisHandler::getErrorMsg()
{
	return error_msg;
}

/*
ʹ�������¼
psw����¼����
�ɹ�����M_REDIS_OK��ʧ�ܷ���<0
*/
int RedisHandler::connectAuth(const string &psw)
{
	string cmd = "auth " + psw;

	pm_rr = (redisReply*)redisCommand(pm_rct, cmd.c_str());

	return handleReply();
}

/*
����redis���ص���Ϣ
value������ָ�룬���ڱ���redis���صĻ������ͣ�valueָ��ָ������ݣ�
array������ָ�룬���ڱ���redis���ص�����
�ɹ�����M_REDIS_OK��ʧ�ܷ���<0
*/
int RedisHandler::handleReply(void* value, redisReply*** array)
{
	if (pm_rct->err)
	{
		error_msg = pm_rct->errstr;
		return M_CONTEXT_ERROR;
	}

	if (pm_rr == NULL)
	{
		error_msg = "auth redisReply is NULL";
		return M_REPLY_ERROR;
	}

	switch (pm_rr->type)
	{
	case REDIS_REPLY_ERROR:
		error_msg = pm_rr->str;
		return M_EXE_COMMAND_ERROR;
	case REDIS_REPLY_STATUS:
		if (!strcmp(pm_rr->str, "OK"))
			return M_REDIS_OK;
		else
		{
			error_msg = pm_rr->str;
			return M_EXE_COMMAND_ERROR;
		}
	case REDIS_REPLY_INTEGER:
		*(int*)value = pm_rr->integer;
		return M_REDIS_OK;
	case REDIS_REPLY_STRING:
		*(string*)value = pm_rr->str;
		return M_REDIS_OK;
	case REDIS_REPLY_NIL:
		*(string*)value = "";
		return M_REDIS_OK;
	case REDIS_REPLY_ARRAY:
		*(int*)value = pm_rr->elements;
		*array = pm_rr->element;
		return M_REDIS_OK;
	default:
		error_msg = "unknow reply type";
		return M_EXE_COMMAND_ERROR;
	}
}

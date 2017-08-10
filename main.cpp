#include <iostream>
#include <string>
#include "redis_handler.h"
using namespace std;

int main()
{
	RedisHandler* rh = new RedisHandler();
	int ret;

	//���Ӳ���
	cout << "�������: " << "��ַ����" << endl;
	ret = rh->connect("34.15.14.15", 6379, "linesum");
	if (ret != M_REDIS_OK)
		cout << "redis error: " << rh->getErrorMsg() << endl;

	cout << "�������: " << "�˿ڴ���" << endl;
	ret = rh->connect("127.0.0.1", 1234, "linesum");
	if (ret != M_REDIS_OK)
		cout << "redis error: " << rh->getErrorMsg() << endl;

	cout << "�������: " << "�������" << endl;
	ret = rh->connect("127.0.0.1", 6479, "linsum");
	if (ret != M_REDIS_OK)
		cout << "redis error: " << rh->getErrorMsg() << endl;


	ret = rh->connect("127.0.0.1", 6479, "linesum");
	if (ret != M_REDIS_OK)
	{
		cout << "redis error: " << rh->getErrorMsg() << endl;
		return ret;
	}


	//set����
	cout << "�������: " << "set����value����" << endl;
	ret = rh->setValue("key11", "");
	if (ret != M_REDIS_OK)
		cout << "redis error: " << rh->getErrorMsg() << endl;


	ret = rh->setValue("key11", "value11");
	if (ret != M_REDIS_OK)
	{
		cout << "redis error: " << rh->getErrorMsg() << endl;
		return ret;
	}

	ret = rh->setValue("key22", "value22");
	if (ret != M_REDIS_OK)
	{
		cout << "redis error: " << rh->getErrorMsg() << endl;
		return ret;
	}


	//get����
	string str;
	cout << "�������: " << "get����key����" << endl;
	ret = rh->getValue("key1111", str);
	if (ret != M_REDIS_OK)
		cout << "redis error: " << rh->getErrorMsg() << endl;

	ret = rh->getValue("key11", str);
	if (ret != M_REDIS_OK)
	{
		cout << "redis error: " << rh->getErrorMsg() << endl;
		return ret;
	}
	else
		cout << "value : " << str << endl;



	//print����
	ret = rh->printAll();
	if (ret != M_REDIS_OK)
	{
		cout << "redis error: " << rh->getErrorMsg() << endl;
		return ret;
	}


	//del����
	cout << "�������: " << "ɾ�������ڵ�key" << endl;
	ret = rh->delKey("key1111");
	if (ret != M_REDIS_OK)
		cout << "redis error: " << rh->getErrorMsg() << endl;


	ret = rh->delKey("key11");
	if (ret != M_REDIS_OK)
	{
		cout << "redis error: " << rh->getErrorMsg() << endl;
		return ret;
	}

	delete rh;

	return 0;
}
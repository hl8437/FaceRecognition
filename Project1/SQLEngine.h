//#pragma once
//
//#include <mysql.h>
//#include <winsock.h>
//#include <Windows.h>
//#include <stdio.h>
//
//
//class SQLEngine
//{
//private:
//	MYSQL mysql;		//mysql����
//	MYSQL_RES *res;		//�����е�һ����ѯ�����
//	char query[150];	//��ѯ���
//	MYSQL_ROW column;	//�����ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���
//
//public:
//	SQLEngine();
//	~SQLEngine();
//	bool connectDatabase();
//	void freeConnect();
//	bool queryDatabase(char * Query);
//
//};
//

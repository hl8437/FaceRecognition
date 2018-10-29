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
//	MYSQL mysql;		//mysql连接
//	MYSQL_RES *res;		//返回行的一个查询结果集
//	char query[150];	//查询语句
//	MYSQL_ROW column;	//行数据的类型安全(type-safe)的表示，表示数据行的列
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

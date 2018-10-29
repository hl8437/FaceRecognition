//#include "SQLEngine.h"
//#include <iostream>
//
//
//
//SQLEngine::SQLEngine()
//{
//}
//
//
//SQLEngine::~SQLEngine()
//{
//}
//
///* 初始化SQLEngine */
//bool SQLEngine::connectDatabase()
//{
//	mysql_init(&mysql);
//
//	if (!(mysql_real_connect(&mysql, "localhost", "root", "931224", "face", 3306, NULL, 0)))
//	{
//		printf("Error connecting to database:%s\n", mysql_error(&mysql));
//		return false;
//	}
//	else
//	{
//		printf("Connected...\n");
//		return true;
//	}
//}
//
///* 释放资源 */
//void SQLEngine::freeConnect()
//{
//	mysql_free_result(res);
//	mysql_close(&mysql);
//}
//
//bool SQLEngine::queryDatabase(char* Query)
//{
//
//	sprintf(query, Query);
//	 std::cout << query << std::endl;
//	//设置编码格式，否则cmd下中文乱码
//	mysql_query(&mysql, "set names gbk"); 
//
//	if (mysql_query(&mysql, query))
//	{
//		printf("Query failed (%s)\n", mysql_error(&mysql));
//		return false;
//	}
//	else
//	{
//		printf("query success\n");
//	}
//	//获取结果集
//	if (!(res = mysql_store_result(&mysql)))
//	{
//		printf("Couldn't get result from %s\n", mysql_error(&mysql));
//		return false;
//	}
//
//	//打印数据行数
//	printf("number of dataline returned: %d\n", (int)mysql_affected_rows(&mysql));
//
//	//获取字段的信息
//	char *str_field[32];  //定义一个字符串数组存储字段信息
//	for (int i = 0; i < 4; i++)   //在已知字段数量的情况下获取字段名
//	{
//		str_field[i] = mysql_fetch_field(res)->name;
//	}
//	for (int i = 0; i < 4; i++)   //打印字段
//		printf("%10s\t", str_field[i]);
//	printf("\n");
//	//打印获取的数据
//	while (column = mysql_fetch_row(res))   //在已知字段数量情况下，获取并打印下一行
//	{
//		printf("%10s\t%10s\t%10s\t%10s\n", column[0], column[1], column[2], column[3]);  //column是列数组
//	}
//	return true;
//}
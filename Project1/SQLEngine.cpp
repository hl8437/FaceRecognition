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
///* ��ʼ��SQLEngine */
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
///* �ͷ���Դ */
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
//	//���ñ����ʽ������cmd����������
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
//	//��ȡ�����
//	if (!(res = mysql_store_result(&mysql)))
//	{
//		printf("Couldn't get result from %s\n", mysql_error(&mysql));
//		return false;
//	}
//
//	//��ӡ��������
//	printf("number of dataline returned: %d\n", (int)mysql_affected_rows(&mysql));
//
//	//��ȡ�ֶε���Ϣ
//	char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ
//	for (int i = 0; i < 4; i++)   //����֪�ֶ�����������»�ȡ�ֶ���
//	{
//		str_field[i] = mysql_fetch_field(res)->name;
//	}
//	for (int i = 0; i < 4; i++)   //��ӡ�ֶ�
//		printf("%10s\t", str_field[i]);
//	printf("\n");
//	//��ӡ��ȡ������
//	while (column = mysql_fetch_row(res))   //����֪�ֶ���������£���ȡ����ӡ��һ��
//	{
//		printf("%10s\t%10s\t%10s\t%10s\n", column[0], column[1], column[2], column[3]);  //column��������
//	}
//	return true;
//}
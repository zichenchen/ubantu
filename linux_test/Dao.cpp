
#include <iostream>
#include"Dao.h"


Dao* Dao::myDao = nullptr;
pthread_mutex_t Dao::g_mutex_lock;
Dao::Dao()
{
	result = NULL;
	connection = mysql_init(NULL); // ��ʼ�����ݿ����ӱ���
	if (connection == NULL)
	{
		cout << "Error:" << mysql_error(connection);
		exit(1);
	}
}

Dao::~Dao()
{
	if (connection != NULL)  // �ر����ݿ�����
	{
		mysql_close(connection);
	}
}

Dao* Dao::getInstance()
{
	Dao* tmp = myDao;
	if (tmp == nullptr)
	{
		pthread_mutex_lock(&g_mutex_lock);
		tmp = myDao;
		if (tmp == nullptr)
		{
			tmp = new Dao();
			myDao = tmp;
		}
	}
	return myDao;
}


bool Dao::initDB(string host, string user, string pwd, string db_name)
{
	// ����mysql_real_connect����һ�����ݿ�����
	// �ɹ�����MYSQL*���Ӿ����ʧ�ܷ���NULL
	connection = mysql_real_connect(connection, host.c_str(),
		user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);
	if (connection == NULL)
	{
		cout << "Error:" << mysql_error(connection);
		exit(1);
	}
	return true;
}

MYSQL_RES* Dao::exeSQL(string sql)
{
	if (connection==NULL) {
		initDB("localhost", "root", "zi666666", "gateway_phcx");
	}
	if (result != NULL) {
		mysql_free_result(result);
	
	}
	// mysql_query()ִ�гɹ�����0��ʧ�ܷ��ط�0ֵ����PHP�в�һ��
	

	if (mysql_query(connection, sql.c_str()))
	{
		cout << "Query Error:" << mysql_error(connection);
		mysql_rollback(connection);
		exit(1);
	}
	else {

		result = mysql_use_result(connection); // ��ȡ�����
	}
	//for (int i = 0; i < mysql_field_count(connection); ++i)
	//{
	//	// ��ȡ��һ��
	//	row = mysql_fetch_row(result);
	//	if (row <= 0)
	//	{
	//		break;
	//	}
	//	// mysql_num_fields()���ؽ�����е��ֶ���
	//	for (int j = 0; j < mysql_num_fields(result); ++j)
	//	{
	//		MYSQL_FIELD* fied = mysql_fetch_field_direct(result, j);
	//	
	//		cout << fied->name << ":" <<row[j] << " ";
	//	}
	//	cout << endl;
	//}
	return result;
}

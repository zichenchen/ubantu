
#include <iostream>
#include"Dao.h"


Dao* Dao::myDao = nullptr;
pthread_mutex_t Dao::g_mutex_lock;
Dao::Dao()
{
	result = NULL;
	connection = mysql_init(NULL); // 初始化数据库连接变量
	if (connection == NULL)
	{
		cout << "Error:" << mysql_error(connection);
		exit(1);
	}
}

Dao::~Dao()
{
	if (connection != NULL)  // 关闭数据库连接
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
	// 函数mysql_real_connect建立一个数据库连接
	// 成功返回MYSQL*连接句柄，失败返回NULL
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
	// mysql_query()执行成功返回0，失败返回非0值。与PHP中不一样
	

	if (mysql_query(connection, sql.c_str()))
	{
		cout << "Query Error:" << mysql_error(connection);
		mysql_rollback(connection);
		exit(1);
	}
	else {

		result = mysql_use_result(connection); // 获取结果集
	}
	//for (int i = 0; i < mysql_field_count(connection); ++i)
	//{
	//	// 获取下一行
	//	row = mysql_fetch_row(result);
	//	if (row <= 0)
	//	{
	//		break;
	//	}
	//	// mysql_num_fields()返回结果集中的字段数
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

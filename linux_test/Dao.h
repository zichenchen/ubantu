#pragma once
#include <string>
#include"mysql/mysql.h"

using namespace std;
class Dao {
public:
	static Dao* getInstance();
	bool initDB(string host, string user, string pwd, string db_name);
    MYSQL_RES* exeSQL(string sql);
    MYSQL* connection;
    MYSQL_RES* result;
    MYSQL_ROW row;
private:
    Dao();
    Dao(const Dao&);
    Dao& operator=(const Dao&);
    virtual ~Dao();
    class CGarbo                    //
    {
    public:
        CGarbo() {}
        ~CGarbo()
        {
            if (Dao::myDao)
            {
                delete Dao::myDao;
            }
        }
    };
    static CGarbo mCGarbo;
private:
    static Dao* myDao;
    static pthread_mutex_t g_mutex_lock;
};


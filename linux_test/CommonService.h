#pragma once
#include <iostream>
#include"PayloadDeCoder.h"
#include"PayloadEnCoder.h"
#include "DbModmapper.h"
#include"PermissionSechMapper.h"
class CommonService
{
public:
    static CommonService* GetInstance();
    void Moduserinfo(char* buffer);
    void exit(char* buffer);
    void ModexecutiveStatus(char* buffer);
    void recoverexecutive(char* buffer);
    void varifyExecutive(char* buffer,int msg_len);


private:
    //µ¥ÀýÊµÏÖ
    CommonService();
    CommonService(const CommonService&);
    CommonService& operator=(const CommonService&);
    virtual ~CommonService();
    class CGarbo                    //
    {
    public:
        CGarbo() {}
        ~CGarbo()
        {
            if (CommonService::m_pInstance)
            {
                delete CommonService::m_pInstance;
            }
        }
    };
    static CGarbo mCGarbo;
private:
    static CommonService* m_pInstance;
    static pthread_mutex_t g_mutex_lock;
    static DbModmapper dbModmapper;
    static PermissionSechMapper permissionSechMapper;

};

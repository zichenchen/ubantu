#pragma once
#include <iostream>
#include"PayloadDeCoder.h"
#include"PayloadEnCoder.h"
#include "DbModmapper.h"
#include"PermissionSechMapper.h"
class CleanService
{
public:
    static CleanService* GetInstance();
     void clean(char* buffer);
     void clean_IA(char* buffer);
     void clean_AC(char* buffer);
private:
    //µ¥ÀýÊµÏÖ
    CleanService();
    CleanService(const CleanService&);
    CleanService& operator=(const CleanService&);
    virtual ~CleanService();
    class CGarbo                    //
    {
    public:
        CGarbo() {}
        ~CGarbo()
        {
            if (CleanService::m_pInstance)
            {
                delete CleanService::m_pInstance;
            }
        }
    };
    static CGarbo mCGarbo;
private:
    static CleanService* m_pInstance;
    static pthread_mutex_t g_mutex_lock;
    static DbModmapper dbModmapper;
    static PermissionSechMapper permissionSechMapper;

};

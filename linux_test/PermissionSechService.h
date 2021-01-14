#pragma once
#include <iostream>
#include"PayloadDeCoder.h"
#include"PayloadEnCoder.h"
#include "PermissionSechMapper.h"
class PermissionSechService
{
public:
    static PermissionSechService* GetInstance();
    static PermissionSechService* NewInstance();
    void Print();
    void permissionSech(char* buffer);
private:
    //µ¥ÀýÊµÏÖ
    PermissionSechService();
    PermissionSechService(const PermissionSechService&);
    PermissionSechService& operator=(const PermissionSechService&);
    virtual ~PermissionSechService();
    class CGarbo                    //
    {
    public:
        CGarbo() {}
        ~CGarbo()
        {
            if (PermissionSechService::m_pInstance)
            {
                delete PermissionSechService::m_pInstance;
            }
        }
    };
    static CGarbo mCGarbo;
private:
    static PermissionSechService* m_pInstance;
    static pthread_mutex_t g_mutex_lock;
    static PermissionSechMapper permissionSechMapper;

};

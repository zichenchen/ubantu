#pragma once
#include <iostream>
#include"PayloadDeCoder.h"
#include"PayloadEnCoder.h"
#include "IdentityAuthMapper.h"
#include "LoginMessage.h"
class IdentityAuthService
{
public:
    static IdentityAuthService* GetInstance();
    static IdentityAuthService* NewInstance();
    void Print();
    void identityAuth(char* buffer);
private:
    //µ¥ÀýÊµÏÖ
    IdentityAuthService();
    IdentityAuthService(const IdentityAuthService&);
    IdentityAuthService& operator=(const IdentityAuthService&);
    virtual ~IdentityAuthService();
    class CGarbo                    //
    {
    public:
        CGarbo() {}
        ~CGarbo()
        {
            if (IdentityAuthService::m_pInstance)
            {
                delete IdentityAuthService::m_pInstance;
            }
        }
    };
    static CGarbo mCGarbo;
private:
    static IdentityAuthService* m_pInstance;
    static pthread_mutex_t g_mutex_lock;
    static IdentityAuthMapper identityAuthMapper;

};

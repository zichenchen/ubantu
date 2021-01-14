
#include "PermissionSechService.h"
#include "IAResultMessage.h"
#include "MyTcpListener.h"
#include "Usertype.h"
#include"ACResultMessage.h"


using namespace std;
//Singleton.cpp  
PermissionSechService* PermissionSechService::m_pInstance = nullptr;
pthread_mutex_t PermissionSechService::g_mutex_lock;
PermissionSechMapper PermissionSechService::permissionSechMapper;


PermissionSechService::PermissionSechService()
{

}


PermissionSechService::~PermissionSechService()
{

}

PermissionSechService* PermissionSechService::GetInstance()
{
    PermissionSechService* tmp = m_pInstance;
    if (tmp == nullptr)
    {
        pthread_mutex_lock(&g_mutex_lock);
        tmp = m_pInstance;
        if (tmp == nullptr)
        {
            tmp = new PermissionSechService();
            m_pInstance = tmp;
        }
    }
    return m_pInstance;
}

PermissionSechService* PermissionSechService::NewInstance()
{

    if (PermissionSechService::m_pInstance != NULL) {
        delete PermissionSechService::m_pInstance;
        PermissionSechService::m_pInstance = NULL;
        PermissionSechService::m_pInstance = new PermissionSechService();
    }
    else {
        PermissionSechService::m_pInstance = new PermissionSechService();
    }
    return  PermissionSechService::m_pInstance;
}

void PermissionSechService::Print()
{
    std::cout << "我的实例内存地址是:" << this << std::endl;
}

void PermissionSechService::permissionSech(char* buffer)
{   
    rttr::variant iaResultMessage = PayloadDeCoder::GenerateObj("IAResultMessage", buffer);
    rttr::type obj_type = rttr::type::get_by_name("IAResultMessage");
   
    IAResultMessage* obj_iaResultMessage = iaResultMessage.get_value<IAResultMessage*>();
    list<rttr::variant> usertypeList = permissionSechMapper.findusertypeListByUsertypeCode(obj_iaResultMessage->getUsertypeCode());
    map<rttr::variant, rttr::variant,cmp_key_Rule> permissionMap;
    for(rttr::variant usertype : usertypeList)
    {
        Usertype* obj_usertype = usertype.get_value<Usertype*>();
       rttr::variant rule = permissionSechMapper.findruleByRuleCode(obj_usertype->getRuleCode());  
        rttr::variant web = permissionSechMapper.findwebByWebCode(obj_usertype->getWebCode());    
        permissionMap.insert(map<rttr::variant, rttr::variant>::value_type(rule, web));
    }
    ACResultMessage obj_acResultMessage;
    obj_acResultMessage.setPermissionMap(permissionMap);
    obj_acResultMessage.setUsertypeArrayList(usertypeList);
    obj_acResultMessage.setSessionId(obj_iaResultMessage->getSessionId());
    obj_acResultMessage.setUserIp(obj_iaResultMessage->getUserIp());
    obj_acResultMessage.setUserPort(obj_iaResultMessage->getUserPort());
    obj_acResultMessage.setUserName(obj_iaResultMessage->getUserName());

    rttr::variant acResultMessage_var = obj_acResultMessage;
    const char* resultdata = PayloadEnCoder::GeneratePkgBuffer("ACResultMessage", acResultMessage_var, 0);
    char obj_len_p[4];
    memcpy(obj_len_p, resultdata, sizeof(int));
    int obj_len = bytes2T<int>(obj_len_p);
    int sessionId_len = obj_iaResultMessage->getSessionId().length();
    int send_msg_len = obj_len + 24 + 2 + sessionId_len;
    string send_msg_type = enumType_match(enumType::EXE_AC_R_MSG);//消息类别
    char* send_msg_len_p = T2bytes<int>(send_msg_len);//消息长度
    char send_msg_buffer[send_msg_len + 4];//创建缓存组
    memset(send_msg_buffer, 0, sizeof(send_msg_buffer));
    memcpy(send_msg_buffer, send_msg_len_p, sizeof(int));
    memcpy(send_msg_buffer + sizeof(int), send_msg_type.c_str(), send_msg_type.length());

    char* sessionId_len_p = int2bytes(sessionId_len);
    memcpy(send_msg_buffer + sizeof(int) + 20, sessionId_len_p, 2);
    memcpy(send_msg_buffer + sizeof(int) + 22, obj_iaResultMessage->getSessionId().c_str(), sessionId_len);
    memcpy(send_msg_buffer + sizeof(int) + 22+sessionId_len, resultdata,obj_len + 4);
    MyTcpListener* Client = MyTcpListener::getInstance();
    Client->mClient->Send((const BYTE*)send_msg_buffer, sizeof(send_msg_buffer));
    delete[]resultdata;


}

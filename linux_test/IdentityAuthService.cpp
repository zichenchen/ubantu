
#include "IdentityAuthService.h"
#include "userinfo.h"
#include "IAResultMessage.h"
#include "MyTcpListener.h"


using namespace std;
//Singleton.cpp  
IdentityAuthService* IdentityAuthService::m_pInstance = nullptr;
pthread_mutex_t IdentityAuthService::g_mutex_lock;
IdentityAuthMapper IdentityAuthService::identityAuthMapper;


IdentityAuthService::IdentityAuthService()
{
  
}


IdentityAuthService::~IdentityAuthService()
{

}

IdentityAuthService* IdentityAuthService::GetInstance()
{
    IdentityAuthService* tmp = m_pInstance;
    if (tmp == nullptr)
    {
        pthread_mutex_lock(&g_mutex_lock);
        tmp = m_pInstance;
        if (tmp == nullptr)
        {
            tmp = new IdentityAuthService();
            m_pInstance = tmp;
        }
    }
    return m_pInstance;
}

IdentityAuthService* IdentityAuthService::NewInstance()
{
 
    if (IdentityAuthService::m_pInstance != NULL) {
        delete IdentityAuthService::m_pInstance;
        IdentityAuthService::m_pInstance = NULL;
        IdentityAuthService::m_pInstance = new IdentityAuthService();
    }
    else {
        IdentityAuthService::m_pInstance = new IdentityAuthService();
    }
    return  IdentityAuthService::m_pInstance;
}

void IdentityAuthService::Print()
{
    std::cout << "我的实例内存地址是:" << this << std::endl;
}

void IdentityAuthService::identityAuth(char* buffer)
{
        rttr::variant loginMessage = PayloadDeCoder::GenerateObj("LoginMessage",buffer);
        rttr::type obj_type = rttr::type::get_by_name("LoginMessage");  
       LoginMessage* obj_loginmessage = loginMessage.get_value<LoginMessage*>();
       rttr::variant userinfo_var = identityAuthMapper.finduserinfoByNameAndPassword(obj_loginmessage->getUserinfoName(), obj_loginmessage->getUserinfoPassword());
       userinfo* obj_userinfo = userinfo_var.get_value<userinfo*>();
       IAResultMessage iaResultMessage;
       string loginstatus;//登录状态
       string send_msg_type= enumType_match(enumType::EXE_IA_R_MSG) ;//消息类别
       /*  obj_type = rttr::type::get_by_name("IAResultMessage");
         rttr::property obj_prop = obj_type.get_property("password");
         rttr::variant iaResultMessage_var = obj_type.create();*/
        if (obj_userinfo->getUserinfoName() == ""||obj_userinfo->getUserinfoStatus()==1003) {
            cout << "登录失败！！" << endl;
            loginstatus=  LoginStatus_enum_match(LoginStatus::IA_FAILED);
        }
        else {
            cout << "登录成功！！"<< obj_userinfo->getUserinfoName() << endl;
           loginstatus= LoginStatus_enum_match(LoginStatus::IA_SUCCESSFUL);
           iaResultMessage.setPassword(obj_userinfo->getUserinfoPassword());
           iaResultMessage.setUserName(obj_userinfo->getUserinfoName());
           iaResultMessage.setUsertypeCode(obj_userinfo->getUsertypeCode());
           iaResultMessage.setUserCreatetime(obj_userinfo->getUserinfoCreatetime());
           iaResultMessage.setUserId(obj_userinfo->getUserinfoId());
         

           /*   obj_prop.set_value(iaResultMessage_var, user->getUserinfoPassword());
            obj_prop = obj_type.get_property("username");
            obj_prop.set_value(iaResultMessage_var, user->getUserinfoName());
            obj_prop = obj_type.get_property("usertypecode");
            obj_prop.set_value(iaResultMessage_var, user->getUsertypeCode());
            obj_prop = obj_type.get_property("usercreatetime");
            obj_prop.set_value(iaResultMessage_var, user->getUserinfoCreatetime());
            obj_prop = obj_type.get_property("userid");
            obj_prop.set_value(iaResultMessage_var, user->getUserinfoId());*/


        }
        iaResultMessage.setSessionId(obj_loginmessage->getSessionId());
        iaResultMessage.setUserIp(obj_loginmessage->getUserinfoIp());
        iaResultMessage.setUserPort(obj_loginmessage->getUserinfoPort());
        
        rttr::variant iaResultMessage_var = iaResultMessage;
       /* obj_prop = obj_type.get_property("sessionId");
        obj_prop.set_value(iaResultMessage_var, obj_loginmessage->getSessionId());
        obj_prop = obj_type.get_property("userip");
        obj_prop.set_value(iaResultMessage_var, obj_loginmessage->getUserinfoIp());
        obj_prop = obj_type.get_property("userport");
        obj_prop.set_value(iaResultMessage_var, obj_loginmessage->getUserinfoPort());*/
       const char* resultdata = PayloadEnCoder::GeneratePkgBuffer("IAResultMessage", iaResultMessage_var, 0);
        char obj_len_p[4];
        memcpy(obj_len_p, resultdata, sizeof(int));
        int obj_len = bytes2T<int>(obj_len_p); 
        /*char* obj_array=new char[obj_len +4];
        memset(obj_array, 0, obj_len+4);
        memcpy(obj_array, resultdata, obj_len+4);
        rttr::variant ovj_var = PayloadDeCoder::GenerateObj("IAResultMessage", obj_array);
        IAResultMessage* itets = ovj_var.get_value<IAResultMessage*>();*/
   
       // int send_msg_len = PayloadEnCoder::countwriteindex + 44;//44=send_msg_type(20)+LoginStatus(20)+Len_des(4)
        int sessionId_len = iaResultMessage.getSessionId().length();
        int send_msg_len = obj_len + 44+2+sessionId_len;
        char* send_msg_len_p = T2bytes<int>(send_msg_len);//消息长度
        char send_msg_buffer[send_msg_len+4];//创建缓存组
        /*
        1.消息总长度
        2.消息类型（20字节）
        3.sessionId长度（2字节）
        4.sessionId
        5.登录状态(20字节)
        6.对象数据
        */
        memset(send_msg_buffer,0,sizeof(send_msg_buffer));
        memcpy(send_msg_buffer, send_msg_len_p, sizeof(int));
        memcpy(send_msg_buffer + sizeof(int), send_msg_type.c_str(), send_msg_type.length());
        char* sessionId_len_p = int2bytes(sessionId_len);
        memcpy(send_msg_buffer + sizeof(int)+20, sessionId_len_p, 2);
        memcpy(send_msg_buffer + sizeof(int)+22, iaResultMessage.getSessionId().c_str(), sessionId_len);

        memcpy(send_msg_buffer + sizeof(int)+22+sessionId_len, loginstatus.c_str(), loginstatus.length());
        memcpy(send_msg_buffer + sizeof(int)+42+sessionId_len, resultdata, obj_len+4);
        MyTcpListener* Client = MyTcpListener::getInstance();
        Client->mClient->Send((const BYTE*)send_msg_buffer, sizeof(send_msg_buffer));
        delete []resultdata;
}

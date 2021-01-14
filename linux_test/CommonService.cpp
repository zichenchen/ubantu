
#include "CommonService.h"
#include "MyTcpListener.h"
#include"ACResultMessage.h"
#include"ExitMessage.h"
#include "ExeStatusModMessage.h"
#include "Executive.h"
using namespace std;
//Singleton.cpp  
CommonService* CommonService::m_pInstance = nullptr;
pthread_mutex_t CommonService::g_mutex_lock;
PermissionSechMapper CommonService::permissionSechMapper;
DbModmapper CommonService::dbModmapper;


CommonService::CommonService()
{
}
CommonService::~CommonService()
{

}

CommonService* CommonService::GetInstance()
{
    CommonService* tmp = m_pInstance;
    if (tmp == nullptr)
    {
        pthread_mutex_lock(&g_mutex_lock);
        tmp = m_pInstance;
        if (tmp == nullptr)
        {
            tmp = new CommonService();
            m_pInstance = tmp;
        }
    }
    return m_pInstance;
}

void CommonService::Moduserinfo(char* buffer)
{
    rttr::variant acResultMessage = PayloadDeCoder::GenerateObj("ACResultMessage", buffer);
    ACResultMessage* acResultMessage_obj =acResultMessage.get_value<ACResultMessage*>();
    permissionSechMapper.moduserinfoIpAndPortByIpAndPort(acResultMessage_obj->getUserIp(), acResultMessage_obj->getUserPort(), acResultMessage_obj->getUserName());
    dbModmapper.StatusModByuserinfoName(1002, acResultMessage_obj->getUserName());
    
}

void CommonService::exit(char* buffer)
{
    rttr::variant exitMessage = PayloadDeCoder::GenerateObj("ExitMessage",buffer);
    ExitMessage* exitMessage_obj = exitMessage.get_value<ExitMessage*>();
    dbModmapper.StatusModByuserinfoName(1001,exitMessage_obj->getUsername());
    list<rttr::variant> usertypeList = permissionSechMapper.findusertypeListByName(exitMessage_obj->getUsername());
    map<rttr::variant, rttr::variant,cmp_key_Rule> permissionMap;
    for (rttr::variant usertype : usertypeList)
    {
        Usertype* obj_usertype = usertype.get_value<Usertype*>();
        rttr::variant rule = permissionSechMapper.findruleByRuleCode(obj_usertype->getRuleCode());
        rttr::variant web = permissionSechMapper.findwebByWebCode(obj_usertype->getWebCode());
        permissionMap.insert(map<rttr::variant, rttr::variant>::value_type(rule, web));
    }
    ACResultMessage obj_acResultMessage;
    obj_acResultMessage.setPermissionMap(permissionMap);
    obj_acResultMessage.setUsertypeArrayList(usertypeList);
    obj_acResultMessage.setSessionId(exitMessage_obj->getSessionid());
    obj_acResultMessage.setUserIp(exitMessage_obj->getUserip());
    obj_acResultMessage.setUserName(exitMessage_obj->getUsername());

    rttr::variant acResultMessage_var = obj_acResultMessage;
    const char* resultdata = PayloadEnCoder::GeneratePkgBuffer("ACResultMessage", acResultMessage_var, 0);
    char obj_len_p[4];
    memcpy(obj_len_p, resultdata, sizeof(int));
    int obj_len = bytes2T<int>(obj_len_p);
    int sessionId_len = exitMessage_obj->getSessionid().length();
    int send_msg_len = obj_len + 24 + 2 + sessionId_len;
    string send_msg_type = enumType_match(enumType::EXIT_R_MSG);//消息类别
    char* send_msg_len_p = T2bytes<int>(send_msg_len);//消息长度
    char send_msg_buffer[send_msg_len + 4];//创建缓存组
    memset(send_msg_buffer, 0, sizeof(send_msg_buffer));
    memcpy(send_msg_buffer, send_msg_len_p, sizeof(int));
    memcpy(send_msg_buffer + sizeof(int), send_msg_type.c_str(), send_msg_type.length());

    char* sessionId_len_p = int2bytes(sessionId_len);
    memcpy(send_msg_buffer + sizeof(int) + 20, sessionId_len_p, 2);
    memcpy(send_msg_buffer + sizeof(int) + 22, exitMessage_obj->getSessionid().c_str(), sessionId_len);
    memcpy(send_msg_buffer + sizeof(int) + 22 + sessionId_len, resultdata, obj_len + 4);
    MyTcpListener* Client = MyTcpListener::getInstance();
    Client->mClient->Send((const BYTE*)send_msg_buffer, sizeof(send_msg_buffer));
    delete[]resultdata;

}

void CommonService::ModexecutiveStatus(char* buffer)
{
    rttr::variant exeStatusModMessage = PayloadDeCoder::GenerateObj("ExeStatusModMessage",buffer);
    ExeStatusModMessage* exeStatusModMessage_obj =exeStatusModMessage.get_value<ExeStatusModMessage*>();
    list<rttr::variant> arrayList = exeStatusModMessage_obj->getExecutiveArrayList();
    for (rttr::variant exe : arrayList) {
        Executive* executive = exe.get_value<Executive*>();
        dbModmapper.modexecutivestatusByIpAndPortWithstatusAndobtime(executive->getExecutive_ip(), executive->getExecutive_port()
            , executive->getExecutive_status(), executive->getExecutive_obtime());
    }

}

void CommonService::recoverexecutive(char* buffer)
{
    time_t mintime=0;
    rttr::variant modexecutive;
    list<rttr::variant> unexecutiveArrayList = dbModmapper.getallexecutivelistBystatus(1);
    for (rttr::variant executive : unexecutiveArrayList) {
        Executive* executive_obj = executive.get_value<Executive*>();
        if (mintime == 0 || mintime > StringToDatetime(executive_obj->getExecutive_obtime())) {
            mintime = StringToDatetime(executive_obj->getExecutive_obtime());
            modexecutive = executive;
        }
    }
    list<rttr::variant> depandarrayList =  dbModmapper.getallexecutivelistBystatus(0);
    depandarrayList.push_back(modexecutive);

    ExeStatusModMessage exeStatusModMessage;
    exeStatusModMessage.setExecutiveArrayList(depandarrayList);

    const char* resultdata = PayloadEnCoder::GeneratePkgBuffer("ExeStatusModMessage", exeStatusModMessage, 0);
    char obj_len_p[4];
    memcpy(obj_len_p, resultdata, sizeof(int));
    int obj_len = bytes2T<int>(obj_len_p);

    string send_msg_type = enumType_match(enumType::EXE_RECOVER_R_MSG);//消息类别
  
    int send_msg_len = obj_len + 24;//24=send_msg_type(20)+Len_des(4)
    char* send_msg_len_p = T2bytes<int>(send_msg_len);//消息长度
    char send_msg_buffer[send_msg_len + 4];//创建缓存组
    memset(send_msg_buffer, 0, sizeof(send_msg_buffer));
    memcpy(send_msg_buffer, send_msg_len_p, sizeof(int));
    memcpy(send_msg_buffer + sizeof(int), send_msg_type.c_str(), send_msg_type.length());
    memcpy(send_msg_buffer + sizeof(int) + 20, resultdata, obj_len + 4);
    MyTcpListener* Client = MyTcpListener::getInstance();
    Client->mClient->Send((const BYTE*)send_msg_buffer, sizeof(send_msg_buffer));
    delete[]resultdata;


}

void CommonService::varifyExecutive(char* buffer,int msg_len)
{
    char sessionid_len_p[2];
    memcpy(sessionid_len_p, buffer, 2);
    int sessionid_len = bytes2int(sessionid_len_p);
    char sessionid_p[sessionid_len];
    memcpy(sessionid_p, buffer, sessionid_len);

    char obj_p[msg_len-2-sessionid_len];
    memcpy(obj_p, buffer+sessionid_len+2, msg_len-2-sessionid_len);
     rttr::variant executive = PayloadDeCoder::GenerateObj("Executive", obj_p);
    Executive* executive_obj = executive.get_value<Executive*>();
    rttr::variant executive_var= dbModmapper.getExecutiveByIpAndPort(executive_obj->getExecutive_ip(),executive_obj->getExecutive_port());
    const char* resultdata = PayloadEnCoder::GeneratePkgBuffer("Executive", executive_var, 0);
    char obj_len_p[4];
    memcpy(obj_len_p, resultdata, sizeof(int));
    int obj_len = bytes2T<int>(obj_len_p);
    int send_msg_len = obj_len + 24 + 2 + sessionid_len;
    string send_msg_type = enumType_match(enumType::EXE_VERIFY_R_MSG);//消息类别
    char* send_msg_len_p = T2bytes<int>(send_msg_len);//消息长度
    char send_msg_buffer[send_msg_len + 4];//创建缓存组
    memset(send_msg_buffer, 0, sizeof(send_msg_buffer));
    memcpy(send_msg_buffer, send_msg_len_p, sizeof(int));
    memcpy(send_msg_buffer + sizeof(int), send_msg_type.c_str(), send_msg_type.length());
 
    memcpy(send_msg_buffer + sizeof(int) + 20, sessionid_len_p, 2);
    memcpy(send_msg_buffer + sizeof(int) + 22, sessionid_p, sessionid_len);
    memcpy(send_msg_buffer + sizeof(int) + 22 + sessionid_len, resultdata, obj_len + 4);
    MyTcpListener* Client = MyTcpListener::getInstance();
    Client->mClient->Send((const BYTE*)send_msg_buffer, sizeof(send_msg_buffer));
    delete[]resultdata;


}




#include "CleanService.h"
#include "MyTcpListener.h"
#include"IAResultMessage.h"
#include"ACResultMessage.h"
#include"ExeStatusModMessage.h"
#include"Executive.h"
using namespace std;
//Singleton.cpp  
CleanService* CleanService::m_pInstance = nullptr;
pthread_mutex_t CleanService::g_mutex_lock;
DbModmapper CleanService::dbModmapper;
PermissionSechMapper CleanService::permissionSechMapper;
CleanService::CleanService()
{
}


CleanService::~CleanService()
{
}
CleanService* CleanService::GetInstance()
{
    CleanService* tmp = m_pInstance;
    if (tmp == nullptr)
    {
        pthread_mutex_lock(&g_mutex_lock);
        tmp = m_pInstance;
        if (tmp == nullptr)
        {
            tmp = new CleanService();
            m_pInstance = tmp;
        }
    }
    return m_pInstance;
}

void CleanService::clean(char* buffer)
{
    rttr::variant exeStatusModMessage = PayloadDeCoder::GenerateObj("ExeStatusModMessage",buffer);
    ExeStatusModMessage* exeStatusModMessage_obj = exeStatusModMessage.get_value<ExeStatusModMessage*>();

    list<rttr::variant> executiveList = exeStatusModMessage_obj->getExecutiveArrayList();
    for (rttr::variant exe : executiveList) {
        Executive* executive = exe.get_value<Executive*>();
        dbModmapper.modexecutivestatusByIpAndPortWithstatus(executive->getExecutive_ip(), executive->getExecutive_port(), 0);
    }

}

void CleanService::clean_IA(char* buffer)
{
    char login_status_p[20];
    memcpy(login_status_p, buffer, 20);
    LoginStatus login_status = LoginStatus_type_match(login_status_p);

    char obj_len_p[4];
    memcpy(obj_len_p, buffer + 20, sizeof(int));
    int obj_len = bytes2T<int>(obj_len_p); 
    char obj_p[obj_len + 4];
    memcpy(obj_p, buffer+20, obj_len + 4);
    rttr::variant iaResultMessage_var = PayloadDeCoder::GenerateObj("IAResultMessage", obj_p);
    IAResultMessage* iaResultMessage_obj = iaResultMessage_var.get_value<IAResultMessage*>();
  
    switch (login_status)
    {
    case LoginStatus::IA_SUCCESSFUL:
        {
        dbModmapper.deluserinfoByuserinfoId(iaResultMessage_obj->getUserId());
        userinfo user;
        user.setUserinfoCreatetime(iaResultMessage_obj->getUserCreatetime());
        
        user.setUserinfoIp(iaResultMessage_obj->getUserIp());
        user.setUserinfoName(iaResultMessage_obj->getUserName());
        user.setUserinfoPassword(iaResultMessage_obj->getPassword());
        user.setUserinfoPort(iaResultMessage_obj->getUserPort());
        user.setUsertypeCode(iaResultMessage_obj->getUsertypeCode());
        user.setUserinfoId(iaResultMessage_obj->getUserId());
        dbModmapper.adduserinfoByUser(&user);
        break;
        }
    case LoginStatus::IA_FAILED: {
        dbModmapper.deluserinfoByName(iaResultMessage_obj->getUserName());
        break;
    }
    default:
        break;
    }

}

void CleanService::clean_AC(char* buffer)
{
    rttr::variant acResultMessage = PayloadDeCoder::GenerateObj("ACResultMessage",buffer);
    ACResultMessage* acResultMessage_obj = acResultMessage.get_value<ACResultMessage*>();

    rttr::variant currentuser = dbModmapper.finduserinfoByuserinfoName(acResultMessage_obj->getUserName());
    userinfo* currentuser_obj = currentuser.get_value<userinfo*>();

    list<rttr::variant> currentusertypeList = acResultMessage_obj->getUsertypeArrayList();
    list<rttr::variant> usertypeList = dbModmapper.findusertypelistByusertypeCode(currentuser_obj->getUsertypeCode());

    map<rttr::variant, rttr::variant,cmp_key_Rule>::iterator itor_map;
    map<rttr::variant, rttr::variant,cmp_key_Rule> permissmap = acResultMessage_obj->getPermissionMap();
    for (itor_map = permissmap.begin(); itor_map != permissmap.end(); itor_map++) {
        rttr::variant rule_form_map = itor_map->first;
        Rule* rule_form_map_obj = rule_form_map.get_value<Rule*>();
        rttr::variant web_form_map = itor_map->second;
        Web* web_form_map_obj = web_form_map.get_value<Web*>();

        rttr::variant web_form_sech = permissionSechMapper.findwebByWebCode(web_form_map_obj->getWebCode());
        Web* web_form_sech_obj = web_form_sech.get_value<Web*>();
        if (web_form_sech_obj->getWebCode() == "") {
            dbModmapper.delwebBywebId(web_form_map_obj->getWebId());
            dbModmapper.addwebByweb(web_form_map_obj);
        }
        else {
            if (!CompareTo(web_form_map, web_form_sech, "Web")) {
                dbModmapper.modwebBywebAndwebCode(web_form_map_obj, web_form_sech_obj->getWebCode());
            }
        }

        rttr::variant rule_form_sech = permissionSechMapper.findruleByRuleCode(rule_form_map_obj->getRuleCode());
        Rule* rule_form_sech_obj = rule_form_sech.get_value<Rule*>();
        if (rule_form_sech_obj->getRuleCode() == "") {
            dbModmapper.delruleByruleId(rule_form_map_obj->getRuleId());
            dbModmapper.addruleByrule(rule_form_map_obj);
        }
        else {

            if (!CompareTo(rule_form_map,rule_form_sech,"Rule")) {
                dbModmapper.modruleByruleAndruleCode(rule_form_map_obj, rule_form_sech_obj->getRuleCode());
            }
        }
    }

    list<rttr::variant>::iterator itor_list;
    itor_list= currentusertypeList.begin();
    while (itor_list!=currentusertypeList.end()) {
        rttr::variant usertype_form_list = *itor_list;
        Usertype* usertype_form_list_obj = usertype_form_list.get_value<Usertype*>();
        if (!usertypeList.empty()) {
            list<rttr::variant>::iterator itor_sech= usertypeList.begin();
            list<rttr::variant>::iterator itor_sech_end= usertypeList.end();
           while(itor_sech != usertypeList.end())
            {
                rttr::variant itor_sech_var = *itor_sech;
                Usertype* itor_sech_obj = itor_sech_var.get_value<Usertype*>();
                if (CompareTo(itor_sech_var,usertype_form_list,"Usertype"))
                {
                    itor_sech = usertypeList.erase(itor_sech);
                    break;
                }
                else if (usertype_form_list_obj->getUsertypeId() == itor_sech_obj->getUsertypeId()) {
                    itor_sech = usertypeList.erase(itor_sech);
                }
                itor_sech++;
            }
            if (itor_sech == itor_sech_end)
            {
                dbModmapper.delusertypeByusertypeId(usertype_form_list_obj->getUsertypeId());
                dbModmapper.addusertypeByusertype(usertype_form_list_obj);
            }
        }
        else {
            dbModmapper.delusertypeByusertypeId(usertype_form_list_obj->getUsertypeId());
            dbModmapper.addusertypeByusertype(usertype_form_list_obj);
        }


        /*itor_sech= find(usertypeList.begin(),usertypeList.end(), usertype_form_list);
        if (itor_sech!= usertypeList.end()) {
            itor_sech = usertypeList.erase(itor_sech);
        }
        else {
            dbModmapper.delusertypeByusertypeId(usertype_form_list_obj->getUsertypeId());
            dbModmapper.addusertypeByusertype(usertype_form_list_obj);
        }*/
        itor_list++;
    }
    list<rttr::variant>::iterator itor_sech = usertypeList.begin();
    while (itor_sech != usertypeList.end())
    {
        rttr::variant itor_sech_var = *itor_sech;
        Usertype* itor_sech_obj = itor_sech_var.get_value<Usertype*>();
        dbModmapper.delusertypeByusertypeId(itor_sech_obj->getUsertypeId());
        itor_sech++;
    }

}

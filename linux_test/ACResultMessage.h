#pragma once
#include "rttr/type"
#include "CommonUtil.h"
class ACResultMessage {
public:
	ACResultMessage();
    ~ACResultMessage();
	std::string& getSessionId();
	void setSessionId(std::string& sessionId);

	std::string& getUserName();
	void setUserName(std::string& username);

	std::string& getUserIp();
	void setUserIp(std::string& userip);

	int getUserPort();
	void setUserPort(int userport);

	std::map<rttr::variant, rttr::variant,cmp_key_Rule>& getPermissionMap();
	void  setPermissionMap(std::map<rttr::variant, rttr::variant,cmp_key_Rule>& permissionMap);

	std::list<rttr::variant>& getUsertypeArrayList();
	void  setUsertypeArrayList(std::list<rttr::variant>& usertypeArrayList);

private:
      std::string sessionid;
      std::string username;
      std::string userip;
      int userport;
      std::map<rttr::variant, rttr::variant,cmp_key_Rule> permissionMap;
      std::list<rttr::variant> usertypeArrayList;
    RTTR_ENABLE()
};
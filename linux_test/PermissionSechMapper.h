#pragma once
#include <iostream>
#include"rttr/type.h"
#include "Dao.h"
using namespace std;
class PermissionSechMapper {
public:
	PermissionSechMapper();
	~PermissionSechMapper();
	list<rttr::variant> findusertypeListByUsertypeCode(string usertypeCode);
	list<rttr::variant> findusertypeListByName(string username);
	rttr::variant findwebByWebCode(string webCode);
	rttr::variant findruleByRuleCode(string ruleCode);
	void moduserinfoIpAndPortByIpAndPort(string userinfoIp,  int userinfoPort,string userinfoName);

private:
	Dao* dao;
};
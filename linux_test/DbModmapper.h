#pragma once
#include <iostream>
#include"rttr/type.h"
#include "Dao.h"
#include "userinfo.h"
#include "Web.h"
#include "Rule.h"
#include "Usertype.h"
using namespace std;
class DbModmapper {
public:
	DbModmapper();
	~DbModmapper();
	void deluserinfoByuserinfoId(int userinfoId);
	void adduserinfoByUser(userinfo* userinfo);
	void deluserinfoByName(string username);
	rttr::variant finduserinfoByuserinfoName( string userinfoName);
	list<rttr::variant> findusertypelistByusertypeCode( string usertypeCode);
	void delwebBywebId(int webId);
	void addwebByweb(Web* web);
	void delruleByruleId(int  ruleId);
	void addruleByrule( Rule* rule);
	void modruleByruleAndruleCode(Rule* rule,string ruleCode);
	void modwebBywebAndwebCode(Web* web, string webCode);
	void delusertypeByusertypeId(int usertypeId);
	void addusertypeByusertype(Usertype* usertype);

	void modexecutivestatusWithstatus(int executive_status);
	void modexecutivestatusByIpAndPortWithstatus(string executive_ip, int executive_port,int executive_status);
	void modexecutivestatusByIpAndPortWithstatusAndobtime(string executive_ip,int executive_port, int executive_status, string executive_obtime);

	void StatusModByuserinfoName(int Status, string username);

	list<rttr::variant> getallexecutivelistBystatus(int executive_status);
	rttr::variant getExecutiveByIpAndPort(string executive_ip,int executive_port);
private:
	Dao* dao;
};
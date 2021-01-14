#include"ACResultMessage.h"
#include <rttr/registration>
#include <iostream>

RTTR_REGISTRATION
{
	rttr::registration::class_<ACResultMessage>("ACResultMessage").constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
	.property("sessionid", &ACResultMessage::getSessionId, &ACResultMessage::setSessionId)
	.property("username", &ACResultMessage::getUserName, &ACResultMessage::setUserName)
	.property("userip",&ACResultMessage::getUserIp,&ACResultMessage::setUserIp)
	.property("userport",&ACResultMessage::getUserPort,&ACResultMessage::setUserPort)
	.property("permissionMap",&ACResultMessage::getPermissionMap,&ACResultMessage::setPermissionMap)
	.property("usertypeArrayList",&ACResultMessage::getUsertypeArrayList,&ACResultMessage::setUsertypeArrayList);
}

ACResultMessage::ACResultMessage():userport(0)
{
	std::cout << "Pojo ACResultMessage  Constructor done" << std::endl;
}

ACResultMessage::~ACResultMessage()
{
}

void ACResultMessage::setSessionId(std::string& sessionid) {
	this->sessionid = sessionid;
}
std::string& ACResultMessage::getSessionId() {
	return this->sessionid;
}
std::string& ACResultMessage::getUserName() {
	return this->username;
}
void ACResultMessage::setUserName(std::string& username) {
	this->username = username;
}
std::string& ACResultMessage::getUserIp() {
	return this->userip;
}
void ACResultMessage::setUserIp(std::string& userip) {
	this->userip = userip;
}
int ACResultMessage::getUserPort() {
	return this->userport;
}
void ACResultMessage::setUserPort(int userport) {
	this->userport = userport;
}

std::map<rttr::variant, rttr::variant,cmp_key_Rule>& ACResultMessage::getPermissionMap() {
	return this->permissionMap;
}
void ACResultMessage::setPermissionMap(std::map<rttr::variant, rttr::variant,cmp_key_Rule>& permissionMap) {
	this->permissionMap = permissionMap;
}

std::list<rttr::variant>& ACResultMessage::getUsertypeArrayList() {
	return this->usertypeArrayList;
}
void ACResultMessage::setUsertypeArrayList(std::list<rttr::variant>& usertypeArrayList) {
	this->usertypeArrayList = usertypeArrayList;
}
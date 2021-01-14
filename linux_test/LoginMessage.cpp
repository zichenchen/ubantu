#include"LoginMessage.h"
#include <rttr/registration>
#include <iostream>

RTTR_REGISTRATION
{
	rttr::registration::class_<LoginMessage>("LoginMessage").constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
	.property("SessionId", &LoginMessage::getSessionId, &LoginMessage::setSessionId)
	.property("userinfoName", &LoginMessage::getUserinfoName, &LoginMessage::setUserinfoName)
	.property("userinfoPassword", &LoginMessage::getUserinfoPassword, &LoginMessage::setUserinfoPassword)
	.property("userinfoIp",&LoginMessage::getUserinfoIp,&LoginMessage::setUserinfoIp)
	.property("userinfoPort",&LoginMessage::getUserinfoPort,&LoginMessage::setUserinfoPort);
}

LoginMessage::LoginMessage() :userinfoPort(0)
{
	std::cout << "Pojo LoginMessage  Constructor done" << std::endl;
}

LoginMessage::~LoginMessage()
{
}

void LoginMessage::setSessionId(std::string& sessionId) {
	this->SessionId = sessionId;
}
std::string& LoginMessage::getSessionId() {
	return this->SessionId;
}
std::string& LoginMessage::getUserinfoName() {
	return this->userinfoName;
}
void LoginMessage::setUserinfoName(std::string& userinfoName) {
	this->userinfoName = userinfoName;
}
std::string& LoginMessage::getUserinfoPassword() {
	return this->userinfoPassword;
}
void LoginMessage::setUserinfoPassword(std::string& userinfoPassword) {
	this->userinfoPassword = userinfoPassword;
}

std::string& LoginMessage::getUserinfoIp() {
	return this->userinfoIp;
}
void LoginMessage::setUserinfoIp(std::string& userinfoIp) {
	this->userinfoIp = userinfoIp;
}
int LoginMessage::getUserinfoPort() {
	return this->userinfoPort;
}
void LoginMessage::setUserinfoPort(int userinfoPort) {
	this->userinfoPort = userinfoPort;
}

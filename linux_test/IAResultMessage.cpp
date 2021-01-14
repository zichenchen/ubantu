#include "IAResultMessage.h"
#include <rttr/registration>
#include <iostream>

RTTR_REGISTRATION
{
	rttr::registration::class_<IAResultMessage>("IAResultMessage").constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
	.property("sessionId", &IAResultMessage::getSessionId, &IAResultMessage::setSessionId)
	.property("username", &IAResultMessage::getUserName, &IAResultMessage::setUserName)
	.property("password", &IAResultMessage::getPassword, &IAResultMessage::setPassword)
	.property("usertypecode",&IAResultMessage::getUsertypeCode,&IAResultMessage::setUsertypeCode)
	.property("userip",&IAResultMessage::getUserIp,&IAResultMessage::setUserIp)
	.property("userport",&IAResultMessage::getUserPort,&IAResultMessage::setUserPort)
	.property("usercreatetime",&IAResultMessage::getUserCreatetime,&IAResultMessage::setUserCreatetime)
	.property("userid",&IAResultMessage::getUserId,&IAResultMessage::setUserId);
}
IAResultMessage::IAResultMessage() :userport(0), userid(0), username(""), password(""), usertypecode(""), usercreatetime(""), userip(""), sessionId("")
{
	std::cout << "Pojo IAResultMessage  Constructor done" << std::endl;
}

IAResultMessage::~IAResultMessage()
{
}

std::string& IAResultMessage::getUserName()
{
	return this->username;
}

void IAResultMessage::setUserName(std::string& username)
{
	this->username = username;
}

std::string& IAResultMessage::getPassword()
{
	return this->password;
}

void IAResultMessage::setPassword(std::string& password)
{
	this->password = password;
}

std::string& IAResultMessage::getUsertypeCode()
{
	return this->usertypecode;
}

void IAResultMessage::setUsertypeCode(std::string& usertypeCode)
{
	this->usertypecode = usertypeCode;
}

std::string& IAResultMessage::getUserIp()
{
	return this->userip;
}


void IAResultMessage::setUserIp(std::string& userip)
{
	this->userip = userip;
}

std::string& IAResultMessage::getUserCreatetime()
{
	return this->usercreatetime;
}

void IAResultMessage::setUserCreatetime(std::string& usercreatetime)
{
	this->usercreatetime = usercreatetime;
}

int IAResultMessage::getUserPort()
{
	return this->userport;
}

void IAResultMessage::setUserPort(int userport)
{
	this->userport = userport;
}

std::string& IAResultMessage::getSessionId()
{
	return this->sessionId;
}

void IAResultMessage::setSessionId(std::string& sessionId)
{
	this->sessionId = sessionId;
}

int IAResultMessage::getUserId()
{
	return this->userid;
}

void IAResultMessage::setUserId(int userid)
{
	this->userid = userid;
}

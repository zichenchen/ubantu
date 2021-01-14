#include "userinfo.h"
#include <rttr/registration>
#include <iostream>

RTTR_REGISTRATION
{
	rttr::registration::class_<userinfo>("userinfo").constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
	.property("userinfoName", &userinfo::getUserinfoName, &userinfo::setUserinfoName)
	.property("userinfoId", &userinfo::getUserinfoId, &userinfo::setUserinfoId)
	.property("userinfoPassword", &userinfo::getUserinfoPassword, &userinfo::setUserinfoPassword)
	.property("userinfoStatus",&userinfo::getUserinfoStatus,&userinfo::setUserinfoStatus)
	.property("usertypeCode",&userinfo::getUsertypeCode,&userinfo::setUsertypeCode)
	.property("userinfoPort",&userinfo::getUserinfoPort,&userinfo::setUserinfoPort)
	.property("userinfoIp",&userinfo::getUserinfoIp,&userinfo::setUserinfoIp)
	.property("userinfoCreatetime",&userinfo::getUserinfoCreatetime,&userinfo::setUserinfoCreatetime);
}
userinfo::userinfo() :userinfoId(0), userinfoStatus(0),userinfoPort(0)
{
	std::cout << "Pojo userinfo  Constructor done" << std::endl;
}

userinfo::~userinfo()
{
}

std::string& userinfo::getUserinfoName()
{
	return this->userinfoName;
}

void userinfo::setUserinfoName(std::string& userinfoName)
{
	this->userinfoName = userinfoName;
}

std::string& userinfo::getUserinfoPassword()
{
	return this->userinfoPassword;
}

void userinfo::setUserinfoPassword(std::string& userinfoPassword)
{
	this->userinfoPassword = userinfoPassword;
}

std::string& userinfo::getUsertypeCode()
{
	return this->usertypeCode;
}

void userinfo::setUsertypeCode(std::string& usertypeCode)
{
	this->usertypeCode = usertypeCode;
}

std::string& userinfo::getUserinfoIp()
{
	return this->userinfoIp;
}


void userinfo::setUserinfoIp(std::string& userinfoIp)
{
	this->userinfoIp = userinfoIp;
}

std::string& userinfo::getUserinfoCreatetime()
{
	return this->userinfoCreatetime;
}

void userinfo::setUserinfoCreatetime(std::string& userinfoCreatetime)
{
	this->userinfoCreatetime = userinfoCreatetime;
}

int userinfo::getUserinfoPort()
{
	return this->userinfoPort;
}

void userinfo::setUserinfoPort(int userinfoPort)
{
	this->userinfoPort = userinfoPort;
}

int userinfo::getUserinfoStatus()
{
	return this->userinfoStatus;
}

void userinfo::setUserinfoStatus(int userinfoStatus)
{
	this->userinfoStatus = userinfoStatus;
}

int userinfo::getUserinfoId()
{
	return this->userinfoId;
}

void userinfo::setUserinfoId(int userinfoId)
{
	this->userinfoId = userinfoId;
}

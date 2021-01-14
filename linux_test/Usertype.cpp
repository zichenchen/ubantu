#include "Usertype.h"
#include <rttr/registration>
#include <iostream>

RTTR_REGISTRATION
{
	rttr::registration::class_<Usertype>("Usertype").constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
	.property("usertypeId", &Usertype::getUsertypeId, &Usertype::setUsertypeId)
	.property("usertypeCode", &Usertype::getUsertypeCode, &Usertype::setUsertypeCode)
	.property("usertypeName", &Usertype::getUsertypeName, &Usertype::setUsertypeName)
	.property("webCode",&Usertype::getWebCode,&Usertype::setWebCode)
	.property("ruleCode",&Usertype::getRuleCode,&Usertype::setRuleCode)
	.property("usertypeDesc",&Usertype::getUsertypeDesc,&Usertype::setUsertypeDesc);
}
Usertype::Usertype()
{
}

Usertype::~Usertype()
{
}

std::string& Usertype::getRuleCode()
{
	return this->ruleCode;
}

void Usertype::setRuleCode(std::string& ruleCode)
{
	this->ruleCode = ruleCode;
}

std::string& Usertype::getWebCode()
{
	return this->webCode;
}

void Usertype::setWebCode(std::string& webCode)
{
	this->webCode = webCode;
}

std::string& Usertype::getUsertypeName()
{
	return this->usertypeName;
}

void Usertype::setUsertypeName(std::string& usertypeName)
{
	this->usertypeName = usertypeName;
}

std::string& Usertype::getUsertypeCode()
{
	return this->usertypeCode;
}

void Usertype::setUsertypeCode(std::string& usertypeCode)
{
	this->usertypeCode = usertypeCode;
}

std::string& Usertype::getUsertypeDesc()
{
	return this->usertypeDesc;
}

void Usertype::setUsertypeDesc(std::string& usertypeDesc)
{
	this->usertypeDesc = usertypeDesc;
}

int Usertype::getUsertypeId()
{
	return this->usertypeId;
}

void Usertype::setUsertypeId(int usertypeId)
{
	this->usertypeId = usertypeId;
}

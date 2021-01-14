#include "Web.h"
#include <rttr/registration>
#include <iostream>

RTTR_REGISTRATION
{
	rttr::registration::class_<Web>("Web").constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
	.property("webId", &Web::getWebId, &Web::setWebId)
	.property("webName", &Web::getWebName, &Web::setWebName)
	.property("webCode", &Web::getWebCode, &Web::setWebCode)
	.property("webAddress",&Web::getWebAddress,&Web::setWebAddress)
	.property("webPort",&Web::getWebPort,&Web::setWebPort);
}

Web::Web():webId(0),webName("test"),webCode(""),webAddress(""),webPort(0)
{
}

Web::~Web()
{
}

std::string& Web::getWebCode()
{
	return this->webCode;
}

void Web::setWebCode(std::string& webCode)
{
	this->webCode = webCode;
}

std::string& Web::getWebAddress()
{
	return this->webAddress;
}

void Web::setWebAddress(std::string& webAddress)
{
	this->webAddress = webAddress;
}

std::string& Web::getWebName()
{
	return this->webName;
}

void Web::setWebName(std::string& webName)
{
	this->webName = webName;
}

int Web::getWebPort()
{
	return this->webPort;
}

void Web::setWebPort(int webPort)
{
	this->webPort = webPort;
}

int Web::getWebId()
{
	return this->webId;
}

void Web::setWebId(int webId)
{
	this->webId = webId;
}

#include "ExitMessage.h"
#include <rttr/registration>
#include <iostream>

RTTR_REGISTRATION
{
	rttr::registration::class_<ExitMessage>("ExitMessage").constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
	.property("sessionid", &ExitMessage::getSessionid, &ExitMessage::setSessionid)
	.property("username", &ExitMessage::getUsername, &ExitMessage::setUsername)
	.property("userip", &ExitMessage::getUserip, &ExitMessage::setUserip);
}
ExitMessage::ExitMessage()
{
}

ExitMessage::~ExitMessage()
{
}

std::string& ExitMessage::getSessionid()
{
	return this->sessionid;
}

void ExitMessage::setSessionid(std::string& sessionid)
{
	this->sessionid = sessionid;
}

std::string& ExitMessage::getUsername()
{
	return this->username;
}

void ExitMessage::setUsername(std::string& username)
{
	this->username = username;
}

std::string& ExitMessage::getUserip()
{
	return this->userip;
}

void ExitMessage::setUserip(std::string& userip)
{
	this->userip = userip;
}

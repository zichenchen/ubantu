#include "Executive.h"
#include <rttr/registration>
#include <iostream>

RTTR_REGISTRATION
{
	rttr::registration::class_<Executive>("Executive").constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
	.property("executive_id", &Executive::getExecutive_id, &Executive::setExecutive_id)
	.property("executive_ip", &Executive::getExecutive_ip, &Executive::setExecutive_ip)
	.property("executive_port", &Executive::getExecutive_port, &Executive::setExecutive_port)
	.property("executive_status",&Executive::getExecutive_status,&Executive::setExecutive_status)
	.property("executive_obtime",&Executive::getExecutive_obtime,&Executive::setExecutive_obtime);
}
Executive::Executive()
{
}

Executive::~Executive()
{
}

std::string& Executive::getExecutive_obtime()
{
	return this->executive_obtime;
}

void Executive::setExecutive_obtime(std::string& executive_obtime)
{
	this->executive_obtime = executive_obtime;
}

std::string& Executive::getExecutive_ip()
{
	return this->executive_ip;
}

void Executive::setExecutive_ip(std::string& executive_ip)
{
	this->executive_ip = executive_ip;
}

int Executive::getExecutive_status()
{
	return this->executive_status;
}

void Executive::setExecutive_status(int executive_status)
{
	this->executive_status = executive_status;
}

int Executive::getExecutive_port()
{
	return this->executive_port;
}

void Executive::setExecutive_port(int executive_port)
{
	this->executive_port = executive_port;
}

int Executive::getExecutive_id()
{
	return this->executive_id;
}

void Executive::setExecutive_id(int executive_id)
{
	this->executive_id = executive_id;
}

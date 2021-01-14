#include "VarifyExeMessage.h"
#include <rttr/registration>
#include <iostream>

RTTR_REGISTRATION
{
	rttr::registration::class_<VarifyExeMessage>("VarifyExeMessage").constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
	.property("sessionid", &VarifyExeMessage::getSessionId, &VarifyExeMessage::setSessionId)
	.property("executive", &VarifyExeMessage::getExecutive, &VarifyExeMessage::setExecutive);
}
VarifyExeMessage::VarifyExeMessage()
{
	std::cout << "Pojo VarifyExeMessage  Constructor done" << std::endl;
}

VarifyExeMessage::~VarifyExeMessage()
{
}

void VarifyExeMessage::setSessionId(std::string& sessionid) {
	this->sessionid = sessionid;
}
std::string& VarifyExeMessage::getSessionId() {
	return this->sessionid;
}

void VarifyExeMessage::setExecutive(rttr::variant& executive) {
	this->executive = executive;
}
rttr::variant& VarifyExeMessage::getExecutive() {
	return this->executive;
}
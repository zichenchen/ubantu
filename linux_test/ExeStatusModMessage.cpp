#include "ExeStatusModMessage.h"
#include <rttr/registration>
#include <iostream>

RTTR_REGISTRATION
{
	rttr::registration::class_<ExeStatusModMessage>("ExeStatusModMessage").constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
	.property("executiveArrayList", &ExeStatusModMessage::getExecutiveArrayList, &ExeStatusModMessage::setExecutiveArrayList);
}
ExeStatusModMessage::ExeStatusModMessage()
{
}

ExeStatusModMessage::~ExeStatusModMessage()
{
}

std::list<rttr::variant>& ExeStatusModMessage::getExecutiveArrayList()
{
	return this->executiveArrayList;
}

void ExeStatusModMessage::setExecutiveArrayList(std::list<rttr::variant>& executiveArrayList)
{
	this->executiveArrayList = executiveArrayList;
}

#include "Rule.h"
#include <rttr/registration>
#include <iostream>

RTTR_REGISTRATION
{
	rttr::registration::class_<Rule>("Rule").constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
	.property("ruleId", &Rule::getRuleId, &Rule::setRuleId)
	.property("ruleName", &Rule::getRuleName, &Rule::setRuleName)
	.property("ruleCode", &Rule::getRuleCode, &Rule::setRuleCode)
	.property("ruleIp",&Rule::getRuleIp,&Rule::setRuleIp)
	.property("rulePort",&Rule::getRulePort,&Rule::setRulePort)
	.property("ruleP",&Rule::getRuleP,&Rule::setRuleP)
	.property("ruleACTION",&Rule::getRuleACTION,&Rule::setRuleACTION);
	
}


Rule::Rule() /*:ruleId(0), rulePort(0),ruleName("test1"),ruleCode("code1"),ruleIp("	"),ruleP("test"),ruleACTION("test")*/
{

}

Rule::~Rule()
{
}

std::string& Rule::getRuleCode()
{
	// TODO: 在此处插入 return 语句
	return this->ruleCode;
}

void Rule::setRuleCode(std::string& ruleCode)
{
	this->ruleCode = ruleCode;
}

std::string& Rule::getRuleName()
{
	return this->ruleName;
}

void Rule::setRuleName(std::string& ruleName)
{
	this->ruleName = ruleName;
}

std::string& Rule::getRuleIp()
{
	return this->ruleIp;
}

void Rule::setRuleIp(std::string& ruleIp)
{
	this->ruleIp = ruleIp;
}

std::string& Rule::getRuleP()
{
	return this->ruleP;
}

void Rule::setRuleP(std::string& ruleP)
{
	this->ruleP = ruleP;
}

std::string& Rule::getRuleACTION()
{
	return this->ruleACTION;
}

void Rule::setRuleACTION(std::string& ruleACTION)
{
	this->ruleACTION = ruleACTION;
}

int Rule::getRulePort()
{
	return this->rulePort;
}

void Rule::setRulePort(int rulePort)
{
	this->rulePort = rulePort;
}

int Rule::getRuleId()
{
	return this->ruleId;
}

void Rule::setRuleId(int ruleId)
{
	this->ruleId = ruleId;
}

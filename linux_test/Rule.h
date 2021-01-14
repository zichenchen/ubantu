#pragma once
#include "rttr/type"
class Rule {
public:
    Rule();
    ~Rule();
    std::string& getRuleCode();
    void setRuleCode(std::string& ruleCode);

    std::string& getRuleName();
    void setRuleName(std::string& ruleName);

    std::string& getRuleIp();
    void setRuleIp(std::string& ruleIp);

    std::string& getRuleP();
    void setRuleP(std::string& ruleP);

    std::string& getRuleACTION();
    void setRuleACTION(std::string& ruleACTION);

    int getRulePort();
    void setRulePort(int rulePort);
    int getRuleId();
    void setRuleId(int ruleId);


    bool operator==(const Rule& p) const //注意这里的两个const
    {
        return (ruleId == p.ruleId) && ((ruleName.compare(p.ruleName) == 0)) && ((ruleCode.compare(p.ruleCode) == 0))
            && ((ruleIp.compare(p.ruleIp) == 0)) && ((ruleP.compare(p.ruleP) == 0)) && ((ruleACTION.compare(p.ruleACTION) == 0))
            && (rulePort == p.rulePort);
    
    }
  

public:
    int ruleId; 
    std::string ruleName;
    std::string ruleCode;
    std::string ruleIp;
    int rulePort;
    std::string ruleP;
    std::string ruleACTION;
    RTTR_ENABLE()
};

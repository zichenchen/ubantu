#pragma once
#include "rttr/type"
class Usertype {
public:
    Usertype();
    ~Usertype();

    std::string& getRuleCode();
    void setRuleCode(std::string& ruleCode);
    std::string& getWebCode();
    void setWebCode(std::string& webCode);

    std::string& getUsertypeName();
    void setUsertypeName(std::string& usertypeName);

    std::string& getUsertypeCode();
    void setUsertypeCode(std::string& usertypeCode);

    std::string& getUsertypeDesc();
    void setUsertypeDesc(std::string& usertypeDesc);


    int getUsertypeId();
    void setUsertypeId(int usertypeId);

private:
         int usertypeId;
         std::string usertypeCode;
         std::string usertypeName;
         std::string webCode;
         std::string ruleCode;
         std::string usertypeDesc;
    RTTR_ENABLE()
};
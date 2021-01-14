#pragma once
#include "rttr/type"
class userinfo {
public:
    userinfo();
    ~userinfo();
    std::string& getUserinfoName();
    void setUserinfoName(std::string& userinfoName);

    std::string& getUserinfoPassword();
    void setUserinfoPassword(std::string& userinfoPassword);

    std::string& getUsertypeCode();
    void setUsertypeCode(std::string& usertypeCode);

    std::string& getUserinfoIp();
    void setUserinfoIp(std::string& userinfoIp);

    std::string& getUserinfoCreatetime();
    void setUserinfoCreatetime(std::string& userinfoCreatetime);

    int getUserinfoPort();
    void setUserinfoPort(int userinfoPort);

    int getUserinfoStatus();
    void setUserinfoStatus(int userinfoStatus);

    int getUserinfoId();
    void setUserinfoId(int userinfoId);

private:
     std::string userinfoName;
     int userinfoId;
     std::string userinfoPassword;
     int userinfoStatus;
     std::string usertypeCode;
     std::string userinfoIp;
     int userinfoPort;
     std::string userinfoCreatetime;
    RTTR_ENABLE()
};
#pragma once
#include "rttr/type"
class IAResultMessage {
public:
    IAResultMessage();
    ~IAResultMessage();
    std::string& getUserName();
    void setUserName(std::string& username);

    std::string& getPassword();
    void setPassword(std::string& password);

    std::string& getUsertypeCode();
    void setUsertypeCode(std::string& usertypecode);

    std::string& getUserIp();
    void setUserIp(std::string& userip);

    std::string& getUserCreatetime();
    void setUserCreatetime(std::string& usercreatetime);

    int getUserPort();
    void setUserPort(int userport);

    std::string& getSessionId();
    void setSessionId(std::string& sessionId);

    int getUserId();
    void setUserId(int userid);

private:
      std::string sessionId;//这个必须为第一位
      std::string username;
      std::string password;
      std::string usertypecode;
      std::string userip;
      int userport;
      std::string usercreatetime;
      int userid;
    RTTR_ENABLE()
};
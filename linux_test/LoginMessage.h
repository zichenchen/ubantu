#pragma once
#include "rttr/type"
class LoginMessage {
public:
    LoginMessage();
    ~LoginMessage();
    std::string& getSessionId();
    void setSessionId(std::string& sessionId);

    std::string& getUserinfoName();
    void setUserinfoName(std::string& userinfoName);

    std::string& getUserinfoPassword();
    void setUserinfoPassword(std::string& userinfoPassword);

    std::string& getUserinfoIp();
    void setUserinfoIp(std::string& userinfoIp);

    int getUserinfoPort();
    void setUserinfoPort(int userinfoPort);


private:
    std::string SessionId;
    std::string userinfoName;
    std::string userinfoPassword;
    std::string userinfoIp;
    int userinfoPort;
    RTTR_ENABLE()
};
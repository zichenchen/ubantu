#pragma once
#include "rttr/type"
class ExitMessage {
public:
    ExitMessage();
    ~ExitMessage();
    std::string& getSessionid();
    void setSessionid(std::string& sessionid);

    std::string& getUsername();
    void setUsername(std::string& username);

    std::string& getUserip();
    void setUserip(std::string& userip);
   ;

private:
     std::string sessionid;
     std::string username;
     std::string userip;
    RTTR_ENABLE()
};
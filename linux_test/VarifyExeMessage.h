#pragma once
#include "rttr/type"
#include <string>
class VarifyExeMessage {
public:
    VarifyExeMessage();
    ~VarifyExeMessage();
  

    std::string& getSessionId();
    void setSessionId(std::string& sessionId);

   rttr::variant& getExecutive();
    void setExecutive(rttr::variant& Executive);

  

private:
    std::string sessionid;
    rttr::variant executive;
    RTTR_ENABLE()
};
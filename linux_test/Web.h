#pragma once
#include "rttr/type"
class Web {
public:
    Web();
    ~Web();

    std::string& getWebCode();
    void setWebCode(std::string& webCode);

    std::string& getWebAddress();
    void setWebAddress(std::string& webAddress);

    std::string& getWebName();
    void setWebName(std::string& webName);

    int getWebPort();
    void setWebPort(int webPort);
    int getWebId();
    void setWebId(int webId);
    bool operator==(const Web& p) const //注意这里的两个const
    {
        return (webId == p.webId) && ((webCode.compare(p.webCode) == 0)) && ((webAddress.compare(p.webAddress) == 0))
            && ((webName.compare(p.webName) == 0)) && (webPort == p.webPort);
    }

private:
   
        int webId;
        std::string webCode;
        std::string webAddress;
        std::string webName;
        int webPort;
    RTTR_ENABLE()
};
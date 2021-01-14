#pragma once
#include "rttr/type"
class Executive {
public:
    Executive();
    ~Executive();

    std::string& getExecutive_obtime();
    void setExecutive_obtime(std::string& executive_obtime);

    std::string& getExecutive_ip();
    void setExecutive_ip(std::string& executive_ip);
    int getExecutive_status();
    void setExecutive_status(int executive_status);

    int getExecutive_port();
    void setExecutive_port(int executive_port);
    int getExecutive_id();
    void setExecutive_id(int executive_id);

private:
    int executive_id;
     std::string executive_ip;
     int executive_port;
     int executive_status;
     std::string executive_obtime;
    RTTR_ENABLE()
};
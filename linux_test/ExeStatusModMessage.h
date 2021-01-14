#pragma once
#include "rttr/type"
class ExeStatusModMessage {
public:
    ExeStatusModMessage();
    ~ExeStatusModMessage();
    std::list<rttr::variant>& getExecutiveArrayList();
    void  setExecutiveArrayList(std::list<rttr::variant>& executiveArrayList);

private:
    std::list<rttr::variant> executiveArrayList;
    RTTR_ENABLE()
};
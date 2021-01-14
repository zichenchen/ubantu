#pragma once
#include <iostream>
#include"rttr/type.h"
#include"CommonUtil.h"

class PayloadDeCoder
{
public:
    static rttr::variant GenerateObj(std::string command, char* obj_array);
    static void fillData(rttr::variant& obj_var, rttr::type obj_type, char* buffer);
    static void WriteToVar(rttr::property prop, rttr::variant& obj_var, char* buffer);
    static int countreadindex;
};

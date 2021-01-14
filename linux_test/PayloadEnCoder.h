#pragma once
#include <iostream>
#include"rttr/type.h"
#include"CommonUtil.h"


class PayloadEnCoder
{
public:

    static char* GeneratePkgBuffer(std::string command, rttr::variant obj, int countindex);
    static void ConvData(rttr::type obj_type, rttr::variant obj);
    static void WriteToBuffer(const rttr::property* prop, rttr::variant obj);
    static int countwriteindex;
    static char buffer[4096];

};

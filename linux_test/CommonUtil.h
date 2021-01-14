
#pragma once

#ifndef __CommonUtil__
#define __CommonUtil__
#pragma warning( disable : 4996 )
#include <time.h>
#include <string.h>
#include <string>
#include"rttr/type.h"
#include <iostream>

template<typename T>
static T bytes2T( char* bytes)
{
    int i, j, k;
    T res = 0;
    int n = sizeof(T);
    for (i = 0, j = n - 1; i <= (n - 1) / 2; i++, j--)
    {
        char k = bytes[i];
        bytes[i] = bytes[j];
        bytes[j] = k;
    }

    memcpy(&res, bytes, n);
    return res;
}

template<typename T>
static  char* T2bytes(T u)
{
    int i, j, k;
    int n = sizeof(T);
     char* b = new  char[n];
    memcpy(b, &u, n);
    for (i = 0, j = n - 1; i <= (n - 1) / 2; i++, j--)
    {
        char k = b[i];
        b[i] = b[j];
        b[j] = k;
    }
    return b;
}

static  char* int2bytes(int u)
{

     char* b = new  char[2];
    memcpy(b, &u, 2);
    char k = b[1];
    b[1] = b[0];
    b[0] = k;

    return b;
}

static int bytes2int( char* bytes)
{
    int res = 0;
    char k = bytes[1];
    bytes[1] = bytes[0];
    bytes[0] = k;
    memcpy(&res, bytes, 2);
    return res;
}

static void  del_sp(char* src, int len)    // ɾ��C����ַ����еĿո�
{
    char* fp = src;
    while (len > 0) {
        if (*src != '\0') { // ������ǿո�͸���
            *fp = *src;
            fp++;
        }
        src++;
        len--;
    }
    *fp = '\0'; //����ַ���

}

struct cmp_key_Rule
{
    bool operator()(const rttr::variant& k1, const rttr::variant& k2)const
    {
        rttr::type type = k1.get_type().get_wrapped_type().get_raw_type();

        for (auto& prop : type.get_properties())
        {
            if (!prop.get_value(k1).to_string().compare(prop.get_value(k2).to_string()) == 0) {
                return true;
            }


        }
        /* if ((k1.ruleId == p.ruleId) && ((k1.ruleName.compare(p.ruleName) == 0)) && ((k1.ruleCode.compare(p.ruleCode) == 0))
             && ((k1.ruleIp.compare(p.ruleIp) == 0)) && ((k1.ruleP.compare(p.ruleP) == 0)) && ((k1.ruleACTION.compare(p.ruleACTION) == 0))
             && (k1.rulePort == p.rulePort))
         {
             return true;
         }*/


        return false;
    }
};

static bool CompareTo(rttr::variant var1,rttr::variant var2,std::string classtype) {
    rttr::type obj_type = rttr::type::get_by_name(classtype);
    for (auto& prop : obj_type.get_properties())
    {
        if (!prop.get_value(var1).to_string().compare(prop.get_value(var2).to_string()) == 0) {
            return false;
        }
    }
    return true;
}

static void  WirteDataByType(std::string type,std::string str,rttr::variant obj,rttr::property prop) {
    if (strcmp(type.c_str(), "int") == 0) {
        prop.set_value(obj, atoi(str.c_str()));
    }
    else if((strcmp(type.c_str(), "double") == 0)|| (strcmp(type.c_str(), "float") == 0)){
        prop.set_value(obj, atof(str.c_str()));
    }
    else {
        prop.set_value(obj, str);
    }

}

static time_t StringToDatetime(std::string str)
{
    char* cha = (char*)str.data();             // ��stringת����char*��
    tm tm_;                                    // ����tm�ṹ�塣
    int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
    //sscanf(cha, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);// ��string�洢������ʱ�䣬ת��Ϊint��ʱ������
    tm_.tm_year = year - 1900;                 // �꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬����tm_yearΪint��ʱ������ȥ1900��
    tm_.tm_mon = month - 1;                    // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
    tm_.tm_mday = day;                         // �ա�
    tm_.tm_hour = hour;                        // ʱ��
    tm_.tm_min = minute;                       // �֡�
    tm_.tm_sec = second;                       // �롣
    tm_.tm_isdst = 0;                          // ������ʱ��
    time_t t_ = mktime(&tm_);                  // ��tm�ṹ��ת����time_t��ʽ��
    return t_;                                 // ����ֵ�� 
}

static std::string DatetimeToString(time_t time)
{
    tm* tm_ = localtime(&time);                // ��time_t��ʽת��Ϊtm�ṹ��
    int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
    year = tm_->tm_year + 1900;                // ��ʱ�������꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬������ʱ����intΪtm_year����1900��
    month = tm_->tm_mon + 1;                   // ��ʱ�������£�����tm�ṹ����·ݴ洢��ΧΪ0-11��������ʱ����intΪtm_mon����1��
    day = tm_->tm_mday;                        // ��ʱ�������ա�
    hour = tm_->tm_hour;                       // ��ʱ������ʱ��
    minute = tm_->tm_min;                      // ��ʱ�������֡�
    second = tm_->tm_sec;                      // ��ʱ�������롣
    char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// ����ʱ��ĸ���char*������
    //sprintf(yearStr, "%d", year);              // �ꡣ
    //sprintf(monthStr, "%d", month);            // �¡�
    //sprintf(dayStr, "%d", day);                // �ա�
    //sprintf(hourStr, "%d", hour);              // ʱ��
    //sprintf(minuteStr, "%d", minute);          // �֡�
    if (minuteStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
    {
        minuteStr[2] = '\0';
        minuteStr[1] = minuteStr[0];
        minuteStr[0] = '0';
    }
    /*sprintf(secondStr, "%d", second);  */        // �롣
    if (secondStr[1] == '\0')                  // �����Ϊһλ����5������Ҫת���ַ���Ϊ��λ����05��
    {
        secondStr[2] = '\0';
        secondStr[1] = secondStr[0];
        secondStr[0] = '0';
    }
    char s[20];                                // ����������ʱ��char*������
    //sprintf(s, "%s-%s-%s %s:%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// ��������ʱ����ϲ���
    std::string str(s);                             // ����string����������������ʱ��char*������Ϊ���캯���Ĳ������롣
    return str;                                // ����ת������ʱ����string������
}

enum class LoginStatus { IA_SUCCESSFUL, IA_FAILED};
static LoginStatus LoginStatus_type_match(const char* status_type_p) {
    if (strcmp(status_type_p,"IA_FAILED")==0) {
        return LoginStatus::IA_FAILED;
    }else if(strcmp(status_type_p, "IA_SUCCESSFUL") == 0){
        return LoginStatus::IA_SUCCESSFUL;
    }
    else
    {
        return LoginStatus::IA_SUCCESSFUL;
    }
};
static  std::string LoginStatus_enum_match(LoginStatus statustype_enum) {
    std::string status_type_p;
    switch (statustype_enum)
    {
    case LoginStatus::IA_SUCCESSFUL:
        status_type_p = "IA_SUCCESSFUL";
        break;
    case LoginStatus::IA_FAILED:
        status_type_p = "IA_FAILED";
        break;
    default:
        break;
    }
    return status_type_p;
};

enum class enumType {
    LOGIN_MSG = 1, EXIT_MSG = 2, EXIT_R_MSG = 3, EXE_IA_MSG = 4, EXE_AC_MSG = 5, EXE_IA_R_MSG = 6, EXE_AC_R_MSG = 7, EXE_IA_C_MSG,
    EXE_AC_C_MSG, EXE_STATUS_MOD_MSG, EXE_RECOVER_MSG, EXE_RECOVER_R_MSG, EXE_VERIFY_MSG,
    EXE_VERIFY_R_MSG,FINAL_MSG
};
static enumType Msgtype_match(char* msgtype_p) {
   
    if (strcmp(msgtype_p, "LOGIN_MSG") == 0) {
        std::cout << "LOGIN_MSG" <<std::endl;
        return enumType::LOGIN_MSG;
    }
    else  if (strcmp(msgtype_p, "EXIT_MSG") == 0) {
        return enumType::EXIT_MSG;
    }
    else  if (strcmp(msgtype_p, "EXIT_R_MSG") == 0) {
        return enumType::EXIT_R_MSG;
    }
    else  if (strcmp(msgtype_p, "EXE_IA_MSG") == 0) {
        std::cout << "EXE_IA_MSG" << std::endl;
        return enumType::EXE_IA_MSG;
    }
    else  if (strcmp(msgtype_p, "EXE_AC_MSG") == 0) {
        std::cout << "EXE_AC_MSG" << std::endl;
        return enumType::EXE_AC_MSG;
    }
    else  if (strcmp(msgtype_p, "EXE_IA_R_MSG") == 0) {
        return enumType::EXE_IA_R_MSG;
    }
    else  if (strcmp(msgtype_p, "EXE_AC_R_MSG") == 0) {
        std::cout << "EXE_AC_R_MSG" << std::endl;
        return enumType::EXE_AC_R_MSG;
    }
    else  if (strcmp(msgtype_p, "EXE_IA_C_MSG") == 0) {
        std::cout << "EXE_IA_C_MSG" << std::endl;
        return enumType::EXE_IA_C_MSG;
    }
    else  if (strcmp(msgtype_p, "EXE_AC_C_MSG") == 0) {
        std::cout << "EXE_AC_C_MSG" << std::endl;
        return enumType::EXE_AC_C_MSG;
    }
    else  if (strcmp(msgtype_p, "EXE_STATUS_MOD_MSG") == 0) {
        std::cout << "EXE_STATUS_MOD_MSG" << std::endl;
        return enumType::EXE_STATUS_MOD_MSG;
    }
    else  if (strcmp(msgtype_p, "EXE_RECOVER_MSG") == 0) {
        std::cout << "EXE_RECOVER_MSG" << std::endl;
        return enumType::EXE_RECOVER_MSG;
    }
    else  if (strcmp(msgtype_p, "EXE_RECOVER_R_MSG") == 0) {
        std::cout << "EXE_RECOVER_R_MSG" << std::endl;
        return enumType::EXE_RECOVER_R_MSG;
    }
    else  if (strcmp(msgtype_p, "EXE_VERIFY_MSG") == 0) {
        return enumType::EXE_VERIFY_MSG;
    }
    else  if (strcmp(msgtype_p, "EXE_VERIFY_R_MSG") == 0) {
        return enumType::EXE_VERIFY_R_MSG;
    }
    else  if (strcmp(msgtype_p, "FINAL_MSG") == 0) {
        return enumType::FINAL_MSG;
    }
    std::cout << "no match" << std::endl;
    return enumType::FINAL_MSG;
};

static std::string enumType_match(enumType msgtype_enum)
{
   std::string msgtype_p;
    switch (msgtype_enum)
    {
    case enumType::LOGIN_MSG:
        msgtype_p = "LOGIN_MSG";
        break;
    case enumType::EXIT_MSG:
        msgtype_p = "EXIT_MSG";
        break;
    case enumType::EXIT_R_MSG:
        msgtype_p = "EXIT_R_MSG";
        break;
    case enumType::EXE_IA_MSG:
        msgtype_p = "EXE_IA_MSG";
        break;
    case enumType::EXE_AC_MSG:
        msgtype_p = "EXE_AC_MSG";
        break;
    case enumType::EXE_IA_R_MSG:
        msgtype_p = "EXE_IA_R_MSG";
        break;
    case enumType::EXE_AC_R_MSG:
        msgtype_p = "EXE_AC_R_MSG";
        break;
    case enumType::EXE_IA_C_MSG:
        msgtype_p = "EXE_IA_C_MSG";
        break;
        
    case enumType::EXE_AC_C_MSG:
        msgtype_p = "EXE_AC_C_MSG";
        break;
    case enumType::EXE_STATUS_MOD_MSG:
        msgtype_p = "EXE_STATUS_MOD_MSG";
        break;
    case enumType::EXE_RECOVER_MSG:
        msgtype_p = "EXE_RECOVER_MSG";
        break;
    case enumType::EXE_RECOVER_R_MSG:
        msgtype_p = "EXE_RECOVER_R_MSG";
        break;
    case enumType::EXE_VERIFY_MSG:
        msgtype_p = "EXE_VERIFY_MSG";
        break;
    case enumType::EXE_VERIFY_R_MSG:
        msgtype_p = "EXE_VERIFY_R_MSG";
        break;
    case enumType::FINAL_MSG:
        msgtype_p = "FINAL_MSG";
        break;
    default:
        break;
    }
    return msgtype_p;
};
#define enum_to_string(x) #x
#endif /* defined(__CommonUtil__) */#pragma once

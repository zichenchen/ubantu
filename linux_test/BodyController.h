#pragma once
#include"CommonUtil.h"
#include"IdentityAuthService.h"
#include"CleanService.h"
#include"CommonService.h"
//#include"CleanService.h"
#include"PermissionSechService.h"
//#include"CommonService.h"
class BodyController {
public:
    BodyController();
    ~BodyController();
    void action(enumType msg_type, char* buffer,int msg_len);

private:
   

};

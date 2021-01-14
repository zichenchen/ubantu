#include "BodyController.h"


IdentityAuthService* identityAuthService = IdentityAuthService::GetInstance();
PermissionSechService* permissionSechService = PermissionSechService::GetInstance();
CleanService* cleanService = CleanService::GetInstance();
CommonService* commonService = CommonService::GetInstance();

BodyController::BodyController() {
	
}
BodyController::~BodyController()
{
}
void BodyController::action( enumType msg_type, char* buffer,int msg_len)
{

	switch (msg_type)
	{
	case enumType::EXIT_MSG:
		commonService->exit(buffer);
		break;
	case enumType::EXE_IA_MSG:
		identityAuthService->identityAuth(buffer);
		break;
	case enumType::EXE_AC_MSG:
		permissionSechService->permissionSech(buffer);
		break;
	case enumType::EXE_IA_C_MSG:
		cleanService->clean_IA(buffer);
		identityAuthService = NULL;
		identityAuthService = IdentityAuthService::NewInstance();
		break;
	case enumType::EXE_AC_C_MSG:
		cleanService->clean_AC(buffer);
		permissionSechService = NULL;
		permissionSechService = PermissionSechService::NewInstance();
		break;
	case enumType::EXE_STATUS_MOD_MSG:
		commonService->ModexecutiveStatus(buffer);
		break;
	case enumType::EXE_RECOVER_MSG:
		commonService->recoverexecutive(buffer);
		break;
	case enumType::EXE_RECOVER_R_MSG:
		cleanService->clean(buffer);
		break;
	case enumType::EXE_VERIFY_MSG:
		commonService->varifyExecutive(buffer, msg_len);
		break;

	case enumType::FINAL_MSG:
		commonService->Moduserinfo(buffer);
		break;
	default:
		break;
	}

}

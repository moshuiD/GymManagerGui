#pragma once
#include "Database.h"
int EnterGym(unsigned int id);
int LeaveGym(unsigned int id);
typedef enum {
	AccessManager_MemberNotFound = 1,
	AccessManager_MemberNotEnter,
	AccessManager_NotEnoughMoney,
	AccessManager_MemberInfoListFilled,
}AccessManagerErrorCode;
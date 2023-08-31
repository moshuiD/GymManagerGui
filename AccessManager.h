#pragma once
#include "Database.h"
int EnterGym(unsigned int id);
int LeaveGym(unsigned int id);
typedef enum {
	AccessManager_MemberNotFound = 1,
	AccessManager_MemberNotEnter,
	AccessManager_MemberIsEnter,
	AccessManager_NotEnoughMoney,
	AccessManager_MemberInfoListFilled,
}AccessManagerErrorCode;

AccessManagerErrorCode EnterGym(unsigned int id);
AccessManagerErrorCode LeaveGym(unsigned int id);
AccessManagerErrorCode AddMemberBodyInfo(unsigned int id, unsigned int height, unsigned int weight, float fat);
AccessManagerErrorCode ReplaceBodyInfo(Member* thisMember, char* const date, MemberBodyInfo* memData);
#include "AccessManager.h"

const double feePerSecond = 0.0028;//
static inline time_t Char2Time(char* const t) {
	struct tm timeStruct = { 0 };
	int year, month, day, hour, minute, second;
	sscanf(t, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	timeStruct.tm_year = year - 1900;
	timeStruct.tm_mon = month - 1;
	timeStruct.tm_mday = day;
	timeStruct.tm_hour = hour;
	timeStruct.tm_min = minute;
	timeStruct.tm_sec = second;
	return mktime(&timeStruct);
}
AccessManagerErrorCode EnterGym(unsigned int id) {
	Member* mem = NULL;
	GetMember(id, &mem);
	if (NULL == mem) {
		return AccessManager_MemberNotFound;
	}
	mem->m_State = In;
	time_t currentTime;
	struct tm* info;
	time(&currentTime);
	info = localtime(&currentTime);
	strftime(mem->m_Time.m_szInTime, 512, "%Y-%m-%d %H:%M:%S", info);
	SyncDatabase();
	return STATE_SUCCESS;
}

AccessManagerErrorCode LeaveGym(unsigned int id) {
	Member* mem = NULL;
	GetMember(id, &mem);
	if (NULL == mem) {
		return AccessManager_MemberNotFound;
	}
	if (Out == mem->m_State) {
		return AccessManager_MemberNotEnter;
	}
	mem->m_State = Out;
	float t_Money = mem->m_fmoney;
	time_t inTime = Char2Time(mem->m_Time.m_szInTime);
	time_t currentTime;
	time(&currentTime);
	double interval = difftime(currentTime, inTime);
	if (t_Money - (interval * feePerSecond * 0.8f) < 0) {
		return AccessManager_NotEnoughMoney;
	}
	mem->m_fmoney = t_Money - (interval * feePerSecond * 0.8f);
	SyncDatabase();
	return STATE_SUCCESS;
}
AccessManagerErrorCode AddMemberBodyInfo(unsigned int id, unsigned int height, unsigned int weight, float fat) {
	Member* mem = NULL;
	GetMember(id, mem);
	if (NULL == mem) {
		return AccessManager_MemberNotFound;
	}
	if (Out == mem->m_State) {
		return AccessManager_MemberNotEnter;
	}
	MemberBodyInfo* memberBodyInfo = NewMemberBodyInfo();
	time_t currentTime;
	struct tm* info;
	time(&currentTime);
	info = localtime(&currentTime);
	strftime(memberBodyInfo->m_szDate, 512, "%Y-%m-%d %H:%M:%S", info);
	memberBodyInfo->m_uHeight = height;
	memberBodyInfo->m_uWeight = weight;
	memberBodyInfo->m_fBodyFat = fat;
	if (push_back(mem->m_BodyInfoList->m_Begin, memberBodyInfo) == ~0) {
		FreeMemberBodyInfo(memberBodyInfo);
		return AccessManager_MemberInfoListFilled;
	}
	SyncDatabase();
	return STATE_SUCCESS;
}
AccessManagerErrorCode ReplaceBodyInfo(Member* thisMember, char* const date, MemberBodyInfo* memData) {
	MemberBodyInfoNode* MemberBodyInfo = NULL;
	for (int state = ListFirst(thisMember->m_BodyInfoList->m_Begin, &MemberBodyInfo); STATE_SUCCESS == state; state = ListNext(MemberBodyInfo, &MemberBodyInfo)) {
		if (strcmp(MemberBodyInfo->m_data->m_szDate, date) == 0) {
			FreeMemberBodyInfo(MemberBodyInfo->m_data);
			MemberBodyInfo->m_data = memData;
			SyncDatabase();
		}
	}
}
#include "DataSaveFormat.h"
static char* szThisBuffer;
static void MembersInfoCallBack(void* info) {
	if (NULL == info) {
		return;
	}
	char buff[512] = { 0 };
	MemberBodyInfo* const tempInfo = info;
	sprintf(buff,
		"{"
		"\"m_szDate\": \"%s\", "
		"\"m_uHeight\": \"%u\", "
		"\"m_uWeight\": \"%u\", "
		"\"m_fBodyFat\": %f "
		"},",
		tempInfo->m_szDate,
		tempInfo->m_uHeight,
		tempInfo->m_uWeight,
		tempInfo->m_fBodyFat);
	strcat(szThisBuffer, buff);
}
int Member2Json(Member* const member, char* buffer) {
	szThisBuffer = buffer;
	int returnCode = sprintf(buffer,
		"{"
		"\"m_uID\": %u, "
		"\"m_szName\": \"%s\", "
		"\"m_szDateOfBirth\": \"%s\", "
		"\"m_uAge\": %u, "
		"\"m_Gander\": %d, "
		"\"m_szAddress\": \"%s\", "
		"\"m_szPhone\": \"%s\", "
		"\"m_fmoney\": %f, "
		"\"m_State\": %d, "
		"\"m_Time\": \"%s\", "
		"\"MemberBodyInfo\":[",
		member->m_uID,
		member->m_szName,
		member->m_szDateOfBirth,
		member->m_uAge,
		member->m_Gander,
		member->m_szAddress,
		member->m_szPhone,
		member->m_fmoney,
		member->m_State,
		member->m_Time.m_szInTime);
	if (-1 == returnCode) {
		buffer = '\0';
		return -1;
	}
	for_each((iterator)member->m_BodyInfoList->m_Begin, MembersInfoCallBack);
	buffer[strlen(buffer) - 1] = '\0';
	strcat(buffer, "]}");
	return STATE_SUCCESS;
}
int Json2Member(char* const src, Member* dest) {
	int returnCode = sscanf(src, "{"
		"\"m_uID\": %u, "
		"\"m_szName\": \"%512[^\"]\", "
		"\"m_szDateOfBirth\": \"%512[^\"]\", "
		"\"m_uAge\": %u, "
		"\"m_Gander\": %d, "
		"\"m_szAddress\": \"%512[^\"]\", "
		"\"m_szPhone\": \"%512[^\"]\", "
		"\"m_fmoney\": %f, "
		"\"m_State\": %d, "
		"\"m_Time\": \"%512[^\"]\", "
		"\"MemberBodyInfo\":[",
		&dest->m_uID,
		dest->m_szName,
		dest->m_szDateOfBirth,
		&dest->m_uAge,
		&dest->m_Gander,
		dest->m_szAddress,
		dest->m_szPhone,
		&dest->m_fmoney,
		&dest->m_State,
		dest->m_Time.m_szInTime);
	if (-1 == returnCode) {
		memset(dest, 0, sizeof(Member));
		return -1;
	}
	char* memberBodyInfoNode = strstr(src, "\"MemberBodyInfo\"");
	if (NULL == memberBodyInfoNode) {
		dest->m_BodyInfoList = NULL;
		return STATE_SUCCESS;
	}
	dest->m_BodyInfoList = NewMemberBodyInfoList();
	for (char* bodyInfo = strstr(memberBodyInfoNode, "{"); NULL != bodyInfo; bodyInfo = strstr(bodyInfo, "{")) {
		MemberBodyInfo* bodyInfoNode = NewMemberBodyInfo();
		sscanf(bodyInfo, "{\"m_szDate\": \"%512[^\"]\", \"m_uHeight\": \"%u\", \"m_uWeight\": \"%u\", \"m_fBodyFat\": %f }",
			bodyInfoNode->m_szDate,
			&bodyInfoNode->m_uHeight,
			&bodyInfoNode->m_uWeight,
			&bodyInfoNode->m_fBodyFat);
		push_back(dest->m_BodyInfoList->m_Begin, bodyInfoNode);
		bodyInfo = strchr(bodyInfo, '}');
	}
	return STATE_SUCCESS;
}
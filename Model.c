#include "Model.h"

Member* NewMember() {
	Member* retV = (Member*)calloc(1,sizeof(Member));
	retV->m_szName = (char*)calloc(512,sizeof(char));
	retV->m_szDateOfBirth= (char*)calloc(512, sizeof(char));
	retV->m_szPhone=(char*)calloc(512, sizeof(char));
	retV->m_szAddress= (char*)calloc(512, sizeof(char));
	retV->m_Time.m_szInTime = (char*)calloc(512, sizeof(char));
	retV->m_BodyInfoList = NULL;
	return retV;
}

void FreeMember(Member* member) {
	free(member->m_szName);
	free(member->m_szDateOfBirth);
	free(member->m_szAddress);
	free(member->m_szPhone);
	free(member->m_Time.m_szInTime);
	FreeMemberBodyInfoList(member->m_BodyInfoList);
	free(member);
}

MemberList* NewMemberList() {
	MemberList* retV = calloc(1, sizeof(MemberList));
	retV->m_uMax = ~0;
	retV->m_Begin = retV;
	retV->m_data = NULL;
	retV->m_Next = NULL;
	return retV;
}
static void FreeMemberListCallBack(void* member) {
	FreeMember(member);
}
void FreeMemberList(MemberList* memberList) {
	for_each(memberList->m_Begin, FreeMemberListCallBack);
}
MemberBodyInfoList* NewMemberBodyInfoList() {
	MemberBodyInfoList* retV = calloc(1, sizeof(MemberBodyInfoList));
	retV->m_uMax = 10;
	retV->m_Begin = retV;
	retV->m_data = NULL;
	retV->m_Next = NULL;
	return retV;
}

MemberBodyInfo* NewMemberBodyInfo() {
	MemberBodyInfo* retV = calloc(1, sizeof(MemberBodyInfo));
	retV->m_szDate = calloc(512, sizeof(char));
	return retV;
}
void FreeMemberBodyInfo(MemberBodyInfo* memberBodyInfo) {
	free(memberBodyInfo->m_szDate);
	free(memberBodyInfo);
}
static void FreeMemberBodyInfoListCallBack(void* memberBodyInfo) {
	FreeMemberBodyInfo(memberBodyInfo);
}
void FreeMemberBodyInfoList(MemberBodyInfoList* memberBodyInfoList) {
	for_each(memberBodyInfoList->m_Begin, FreeMemberBodyInfoListCallBack);
}
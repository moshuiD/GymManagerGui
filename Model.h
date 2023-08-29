#pragma once
#include <stdlib.h>
#include "STL.h"
typedef struct {
	char* m_szDate;
	unsigned int m_uHeight;
	unsigned int m_uWeight;
	float m_fBodyFat;
}MemberBodyInfo;

typedef struct MemberBodyInfoNode {
	unsigned int m_uMax;
	struct MemberBodyInfoNode* m_Begin;
	MemberBodyInfo* m_data;
	struct MemberBodyInfoNode* m_Next;
}MemberBodyInfoNode, MemberBodyInfoList;

typedef enum
{
	Male,
	Female,
	Unknown
}Gander;
typedef enum {
	 Out,
	 In
}MemberState;
typedef struct {
	unsigned int m_uID;
	char* m_szName;
	char* m_szDateOfBirth;
	unsigned int m_uAge;
	Gander m_Gander;
	char* m_szAddress;
	char* m_szPhone;
	float m_fmoney;
	MemberState m_State;
	union InOutTimeStamp
	{
		char* m_szInTime;
		char* m_szLeaveTime;
	}m_Time;
	MemberBodyInfoList* m_BodyInfoList;
}Member;

typedef struct MemberNode {
	unsigned int m_uMax;
	struct MemberNode* m_Begin;
	Member* m_data;
	struct MemberNode* m_Next;
}MemberNode, MemberList;

MemberBodyInfo* NewMemberBodyInfo();
void FreeMemberBodyInfo(MemberBodyInfo*);
MemberBodyInfoList* NewMemberBodyInfoList();
void FreeMemberBodyInfoList(MemberBodyInfoList*);

Member* NewMember();
void FreeMember(Member*);
MemberList* NewMemberList();
void FreeMemberList(MemberList*);

#pragma once
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

typedef struct {
	unsigned int m_uID;
	char* m_szName;
	char* m_szDateOfBirth;
	unsigned int m_uAge;
	Gander m_Gander;
	char* m_szAddress;
	char* m_szPhone;
	float m_fmoney;
	MemberBodyInfoList m_BodyInfoList;
}Member;

typedef struct MemberNode {
	unsigned int m_uMax;
	struct MemberNode* m_Begin;
	Member* m_data;
	struct MemberNode* m_Next;
}MemberNode, MemberList;
#pragma once
#include "framework.h"
#include "Model.h"
#include "STL.h"
typedef enum {
	FileSuccess,
	FileOpenError,

}FileHelperState;

FileHelperState InitFileHelper();
inline FileHelperState SaveMemberInfo(Member);
FileHelperState LoadMembers(MemberList*);
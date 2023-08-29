#pragma once
#include "framework.h"
#include "Model.h"
#include "STL.h"
#include "DataSaveFormat.h"
typedef enum {
	FileSuccess,
	FileOpenError,
	FileLoaderMemberError,
}FileHelperState;

FileHelperState InitFileHelper();
inline FileHelperState SaveMemberInfo(Member);
FileHelperState LoadMembers(MemberList*);
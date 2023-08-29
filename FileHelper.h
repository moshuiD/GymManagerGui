#pragma once
#include "framework.h"
#include "Model.h"
#include "STL.h"
#include "DataSaveFormat.h"
typedef enum {
	FileSuccess,
	FileOpenError,
	FileLoaderMemberError,
	FileSaveError,
	FileCloseError
}FileHelperState;

FileHelperState InitFileHelper();
FileHelperState SaveMemberInfo(Member*);
FileHelperState SaveMembers(MemberList*);
FileHelperState LoadMembers(MemberList*);
FileHelperState ClearAll();
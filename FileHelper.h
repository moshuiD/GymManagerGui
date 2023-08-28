#pragma once
#include "framework.h"
#include "Model.h"
typedef enum {
	FileSuccess,
	FileOpenError,

}FileHelperState;

FileHelperState InitFileHelper();
inline FileHelperState SaveMemberInfo(Member);
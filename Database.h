#pragma once
#include "FileHelper.h"
#include "Model.h"
typedef enum {
	DatabaseSuccess,
	LocalDatabaseOpenFaild,
	LocalDatabaseLoaderMemberError,
	LocalDatabaseFileSaveError,
	LocalDatabaseCloseFaild,
	DatabaseAddFaild
}DatabaseState;
//Warning! These database method all not allow in multi-threading
DatabaseState InitDatabase();
DatabaseState AddMember(Member* const);
DatabaseState DeleteMember(unsigned int id);
DatabaseState EditMember(unsigned int id, Member* newInfo);
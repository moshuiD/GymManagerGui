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
DatabaseState EditMember(unsigned int id, Member* const newInfo);
//Member** can be modified but need use SyncDatabase to sync.But I don't recommend doing this!!!
DatabaseState GetMember(unsigned int id, Member**);
//If use GetMember and modified member.U need use this method to sync data to local database.
DatabaseState SyncDatabase();
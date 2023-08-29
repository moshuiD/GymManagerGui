#pragma once
#include "FileHelper.h"
#include "Model.h"
typedef enum {
	DatabaseSuccess,
	LocalDatabaseOpenFaild,
	LocalDatabaseLoaderMemberError,
}DatabaseState;
DatabaseState InitDatabase();
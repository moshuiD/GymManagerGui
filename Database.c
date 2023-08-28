#include "Database.h"
static MemberList memberList;
DatabaseState InitDatabase() {
	FileHelperState fileHelper = InitFileHelper();
	if (FileSuccess != fileHelper) {
		return fileHelper;//Sync with file error codes.
	}
	memberList.m_uMax = ~0;
}

int AddMember(const Member mem) {
	
}
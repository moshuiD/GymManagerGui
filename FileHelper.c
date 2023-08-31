#include "FileHelper.h"

static char szPath[1024];
FileHelperState InitFileHelper() {
	GetCurrentDirectoryA(1024, szPath);
	strcat(szPath, "\\database.db");
	return FileSuccess;
}

FileHelperState SaveMemberInfo(Member* member) {
	FILE* fpLocalDatabase = fopen(szPath, "a+");
	if (NULL == fpLocalDatabase) {
		return FileOpenError;
	}
	char buff[1024] = { 0 };
	if (STATE_SUCCESS != Member2Json(member, buff)) {
		return FileSaveError;
	}
	if (fprintf(fpLocalDatabase, "%s\n", buff) == -1) {
		return FileSaveError;
	}
	return fclose(fpLocalDatabase) == 0 ? FileSuccess : FileCloseError;
}

FileHelperState LoadMembers(MemberList* members) {
	char buff[4096] = { 0 };
	int numOfBytes = 0;
	FILE* fpLocalDatabase = fopen(szPath, "r");
	if (NULL == fpLocalDatabase) {
		return FileOpenError;
	}
	while ((numOfBytes = fgets(buff, sizeof(buff), fpLocalDatabase) > 0)) {
		Member* member = NewMember();
		if (STATE_SUCCESS != Json2Member(buff, member)) {
			FreeMember(member);
			fclose(fpLocalDatabase);
			return FileLoaderMemberError;
		}
		if (STATE_SUCCESS != push_back(members->m_Begin, member)) {
			FreeMember(member);
			fclose(fpLocalDatabase);
			return FileLoaderMemberError;
		}
	}
	return fclose(fpLocalDatabase) == 0 ? FileSuccess : FileCloseError;
}
FileHelperState SaveMembers(MemberList* members) {
	FILE* fpLocalDatabase = fopen(szPath, "a+");
	if (NULL == fpLocalDatabase) {
		return FileOpenError;
	}
	MemberNode* member = NULL;
	for (int state = ListFirst(members->m_Begin, &member); STATE_SUCCESS == state; state = ListNext(member, &member)) {
		char buff[4096] = { 0 };
		if (Member2Json(member->m_data, buff) != STATE_SUCCESS) {
			return FileSaveError;
		}
		if (fprintf(fpLocalDatabase, "%s\n", buff) == -1) { 
			fclose(fpLocalDatabase);
			return FileSaveError; 
		}
	}
	return fclose(fpLocalDatabase) == 0 ? FileSuccess : FileCloseError;
}
FileHelperState ClearAll() {
	FILE* fpLocalDatabase = fopen(szPath, "w");
	if (NULL == fpLocalDatabase) {
		return FileOpenError;
	}
	return fclose(fpLocalDatabase) == 0 ? FileSuccess : FileCloseError;
}

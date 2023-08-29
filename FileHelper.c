#include "FileHelper.h"
static FILE* fpLocalDatabase;
FileHelperState InitFileHelper() {
	char szPath[1024];
	GetCurrentDirectoryA(1024, szPath);
	strcat(szPath, "\\database.db");
	fpLocalDatabase = fopen(szPath, "a+");
	if (NULL == fpLocalDatabase) {
		return FileOpenError;
	}
	return FileSuccess;
}

inline FileHelperState SaveMemberInfo(Member member) {
	char buff[1024] = { 0 };
	Members2Json(&member,buff);
}
FileHelperState LoadMembers(MemberList* members) {
	char buff[1024] = { 0 };
	int numOfBytes = 0;

	while ((numOfBytes = fread(buff, sizeof(char), sizeof(buff), fpLocalDatabase) > 0)) {
		Member* member = NewMember();
		if (-1 == Json2Member(buff, member)) {
			FreeMember(member);
			return FileLoaderMemberError;
		}
		if (-1 == push_back(members->m_Begin, member)){
			FreeMember(member);
			return FileLoaderMemberError;
		}
	}
}
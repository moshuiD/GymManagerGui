#include "FileHelper.h"
static FILE* fpLocalDatabase;
FileHelperState InitFileHelper() {
	fpLocalDatabase = fopen("", "a+");
	if (NULL == fpLocalDatabase) {
		return FileOpenError;
	}
}

inline FileHelperState SaveMemberInfo(Member member) {
	Menbers2Json(member);
}
#include "Database.h"
static MemberList* memberList;
DatabaseState InitDatabase() {
	FileHelperState fileHelper = InitFileHelper();
	if (FileSuccess != fileHelper) {
		return fileHelper;//Sync with file error codes.
	}
	memberList = NewMemberList();
	return LoadMembers(memberList);//load data from local to memory
}

DatabaseState AddMember(Member* const mem) {
	if (push_back(memberList->m_Begin, mem) != STATE_SUCCESS) {
		return DatabaseAddFaild;
	}
	return SaveMemberInfo(mem);
}

DatabaseState DeleteMember(unsigned int id) {
	MemberNode* member = NULL;
	for (int state = ListFirst(memberList, &member); STATE_SUCCESS  == state; state = ListNext(member, &member)) {
		if (member->m_data->m_uID == id) {
			FreeMember(erase(member));
			ClearAll();
			return SaveMembers(memberList);
		}
	}
}

DatabaseState EditMember(unsigned int id,Member* const newInfo) {
	MemberNode* member = NULL;
	for (int state = ListFirst(memberList, &member); STATE_SUCCESS  == state; state = ListNext(member, &member)) {
		if (member->m_data->m_uID == id) {
			FreeMember(member->m_data);
			member->m_data = newInfo;
			ClearAll();
			return SaveMembers(memberList);
		}
	}
}

DatabaseState GetMember(unsigned int id, Member** pOutMember) {
	MemberNode* member = NULL;
	for (int state = ListFirst(memberList, &member); STATE_SUCCESS == state; state = ListNext(member, &member)) {
		if (member->m_data->m_uID == id) {
			*pOutMember = member->m_data;
			return DatabaseSuccess;
		}
	}
	*pOutMember = NULL;
	return DatabaseSuccess;
}

DatabaseState SyncDatabase() {
	ClearAll();
	return SaveMembers(memberList);
}

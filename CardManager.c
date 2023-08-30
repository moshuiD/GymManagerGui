#include "CardManager.h"
Member* InitCardManager() {
	srand(time(0));
	Member* mem = NewMember();
	mem->m_uID = GenerateID();
	return mem;
}
static unsigned int GenerateID() {
	Member* m = NULL;
	unsigned int id = 0;
	do
	{
		id = 10000 + rand() % (99999 - 10000 + 1);
		GetMember(id, &m);
		if (NULL == m) {
			return id;
		}
	} while (m != NULL);
}
int SignUpCard(Member* mem) {
	mem->m_fmoney = 500.f;
	AddMember(mem);
}
int RechargeCard(unsigned int id, float money) {
	Member* mem = NULL;
	GetMember(id, mem);
	if (NULL == mem) {
		return -1;
	}
	mem->m_fmoney += money;
	SyncDatabase();
}

int DeleteCard(unsigned int id)
{
	return DeleteMember(id);
}

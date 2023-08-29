#include "CardManager.h"
int InitCardManager() {
	srand(time(0));
}
static unsigned int GenerateID() {
	Member* m = NULL;
	unsigned int id = 0;
	do
	{
		id = 10000 + rand() % (99999 - 10000 + 1);
		GetMember(id, &m);
	} while (m != NULL);
}
int SignUpCard(char* const name, char* const birthDay, unsigned int age, Gander gander, char* const addr, char* const phone) {
	Member* mem = NewMember();
	mem->m_uID = GenerateID();
	strcpy(mem->m_szName, name);
	strcpy(mem->m_szDateOfBirth, birthDay);
	mem->m_uAge = age;
	mem->m_Gander = gander;
	strcpy(mem->m_szAddress, addr);
	strcpy(mem->m_szPhone, phone);
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
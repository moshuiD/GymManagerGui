#pragma once
#include "Database.h"
Member* InitCardManager();
int SignUpCard(Member* mem);
int RechargeCard(unsigned int id, float money);
int DeleteCard(unsigned int id);
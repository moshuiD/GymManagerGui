#pragma once
#include "Database.h"
int SignUpCard(char* const name, char* const birthDay, unsigned int age, Gander gander, char* const addr, char* const phone);
int RechargeCard(unsigned int id, float money);
#pragma once
#include "framework.h"
#define STATE_SUCCESS 0
typedef struct Node{
	unsigned int m_uMax;
	struct Node* m_Begin;
	void* m_Data;
	struct Node* m_Next;
}* iterator;
typedef void(* _Fn)(void*);

int for_each(iterator, _Fn);
int push_back(iterator, void*);
iterator pop_back(iterator);
iterator erase(iterator);
//Have some Mircosoft style :D
/////////////////////////////////////////
int ListFirst(iterator begin, void* node);
int ListNext(iterator curret, void* node);
/////////////////////////////////////////
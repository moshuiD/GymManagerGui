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
//_FN [in] data maybe NULL
int for_each(iterator, _Fn);
int push_back(iterator, void*);
iterator pop_back(iterator);
iterator erase(iterator);
iterator at(iterator begin, unsigned int index);
//Have some Mircosoft style :D
/////////////////////////////////////////
int ListFirst(iterator begin, void** pNode);
int ListNext(iterator curret, void** pNode);
/////////////////////////////////////////
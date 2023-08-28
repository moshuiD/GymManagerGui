#pragma once
#include "framework.h"
typedef struct Node{
	unsigned int m_uMax;
	struct Node* m_Begin;
	void* m_Data;
	struct Node* m_Next;
}* iterator;
typedef void(* _Fn)(void*);

int for_each(iterator, _Fn);
int push_back(iterator, void*);
int pop_back(iterator);
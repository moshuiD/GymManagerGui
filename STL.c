#include "STL.h"
int for_each(iterator begin, _Fn func) {
	if (IsBadReadPtr(begin, sizeof(iterator))) {
		return -1;
	}
	for (iterator iter = begin; NULL != iter; iter=iter->m_Next)
	{
		func(iter->m_Data);
	}
	return 0;
}
//data need deep copy
int push_back(iterator begin, void* data)
{
	if (IsBadReadPtr(begin, sizeof(iterator))) {
		return -1;
	}
	iterator iNextNode = begin->m_Next;
	while (1) {
		iNextNode = iNextNode->m_Next;
		if (NULL == iNextNode->m_Next) {
			iterator tempNode = (iterator)malloc(sizeof(struct Node));
			tempNode->m_Data = tempNode;
			tempNode->m_Begin = iNextNode->m_Begin;
			tempNode->m_uMax = iNextNode->m_uMax;
			tempNode->m_Next = NULL;
			break;
		}
	}
	return 0;
}
//Need use "free" to free the item
int pop_back(iterator begin) {
	if (IsBadReadPtr(begin, sizeof(iterator))) {
		return -1;
	}
	iterator oldIt = begin;
	for (iterator iter = begin; NULL != iter->m_Next; iter = iter->m_Next) {
		
		if (NULL == iter->m_Next) {
			oldIt->m_Next = NULL;
			
		}
		oldIt = iter;
	}
}
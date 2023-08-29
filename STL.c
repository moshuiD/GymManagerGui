#include "STL.h"
int for_each(iterator begin, _Fn func) {
	if (IsBadReadPtr(begin, sizeof(iterator))) {
		return -1;
	}
	for (iterator iter = begin; NULL != iter; iter = iter->m_Next) {
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

	if (NULL == begin->m_Data) {//The first node.
		begin->m_Data = data;
		begin->m_Next = NULL;
		return 0;
	}
	iterator iter = begin;
	do
	{
		if (NULL == iter->m_Next) {
			iterator tempNode = (iterator)malloc(sizeof(struct Node));
			tempNode->m_Data = data;
			tempNode->m_Begin = iter->m_Begin;
			tempNode->m_uMax = iter->m_uMax;
			tempNode->m_Next = NULL;

			iter->m_Next = tempNode;//mount the next node

			iter = iter->m_Next;
		}
		iter = iter->m_Next;
	} while (NULL != iter);
	return 0;
}
//Need use "free" to free return value
iterator pop_back(iterator begin) {
	if (IsBadReadPtr(begin, sizeof(iterator))) {
		return NULL;
	}
	iterator oldIt = begin;
	for (iterator iter = begin; NULL != iter->m_Next; iter = iter->m_Next) {

		if (NULL == iter->m_Next) {
			oldIt->m_Next = NULL;
			void* data = iter->m_Data;
			free(iter);
			return data;
		}
		oldIt = iter;
	}
}
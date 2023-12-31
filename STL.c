#include "STL.h"
int for_each(iterator begin, _Fn func) {
	if (IsBadReadPtr(begin, sizeof(iterator))) {
		return -1;
	}
	for (iterator iter = begin; NULL != iter; iter = iter->m_Next) {
		func(iter->m_Data);
	}
	return STATE_SUCCESS;
}
//The data must be generated by the Newxxxx
int push_back(iterator begin, void* data)
{
	if (IsBadReadPtr(begin, sizeof(iterator))) {
		return -1;
	}

	if (NULL == begin->m_Data) {//If is the first node.
		begin->m_Data = data;
		begin->m_Next = NULL;
		return STATE_SUCCESS;
	}
	iterator iter = begin;
	int num = 0;
	do
	{
		num++;
		if (num == iter->m_uMax) {
			return -2;
		}
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
	return STATE_SUCCESS;
}
//Need use "Freexxx" to free return value
iterator pop_back(iterator begin) {
	if (IsBadReadPtr(begin, sizeof(iterator))) {
		return NULL;
	}
	iterator oldIt = begin;
	for (iterator iter = begin; NULL != iter; iter = iter->m_Next) {

		if (NULL == iter->m_Next) {
			oldIt->m_Next = NULL;
			void* data = iter->m_Data;
			free(iter);
			return data;
		}
		oldIt = iter;
	}
}
iterator erase(iterator iter) {
	if (NULL == iter->m_Next) {
		return pop_back(iter->m_Begin);
	}
	iterator oldIt = iter->m_Begin;
	for (iterator it = iter->m_Begin; NULL != it->m_Next; it = it->m_Next) {

		if (iter == it) {
			oldIt->m_Next = it->m_Next;
			void* data = it->m_Data;
			free(it);
			return data;
		}
		oldIt = it;
	}
}
iterator at(iterator begin, unsigned int index) {
	int i = 0;
	for (iterator it = begin; NULL != it->m_Next; it = it->m_Next) {
		if (index == i) {
			return it;
		}
		i++;
	}
	return NULL;
}
//Can't ensure data is valid
int ListFirst(iterator begin, void** pNode) {
	if (IsBadReadPtr(begin, sizeof(iterator))) {
		return -1;
	}
	*pNode = begin;
	return STATE_SUCCESS;
}
//Can't ensure data is valid
int ListNext(iterator curret, void** pNode) {
	if (IsBadReadPtr(curret, sizeof(iterator))) {
		return -1;
	}
	if (NULL == curret->m_Next) {
		return -1;
	}
	*pNode = curret->m_Next;
	return STATE_SUCCESS;
}
#pragma once
#include "resource.h"
#include "framework.h"
#include "AccessManager.h"
INT_PTR CALLBACK AddMemberBodyInfoFormCallBack(HWND, UINT, WPARAM, LPARAM);
typedef struct {
	unsigned int m_uHeight;
	unsigned int m_uWeight;
	float m_fFat;
}BodyInfo;
extern BodyInfo g_BodyData;
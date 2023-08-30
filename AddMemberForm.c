#include "AddMemberForm.h"
static HWND g_hDlg = NULL;
static Member* g_member = NULL;

static LRESULT OnNotify(HWND hWnd, NMHDR* lParam)
{
	if (((LPNMHDR)lParam)->code == DTN_DATETIMECHANGE) {
		LPNMDATETIMECHANGE pChange = (LPNMDATETIMECHANGE)lParam;

		SYSTEMTIME selectedTime;
		SendMessage((LPNMHDR)lParam->hwndFrom, DTM_GETSYSTEMTIME, 0, (LPARAM)&selectedTime);
		char birthDayBuff[12] = { 0 };
		sprintf(birthDayBuff, "%04d/%02d/%02d", selectedTime.wYear, selectedTime.wMonth, selectedTime.wDay);
		strcpy(g_member->m_szDateOfBirth, birthDayBuff);

		SYSTEMTIME currentTime;
		GetLocalTime(&currentTime);
		int yearDifference = currentTime.wYear - selectedTime.wYear;
		if (currentTime.wMonth < selectedTime.wMonth ||
			(currentTime.wMonth == selectedTime.wMonth && currentTime.wDay < selectedTime.wDay)) {
			yearDifference--;
		}
		g_member->m_uAge = yearDifference;
		char ageBuff[4] = { 0 };
		sprintf(ageBuff, "%d", yearDifference);
		SetDlgItemText(g_hDlg, IDC_AGE, ageBuff);
	}

	return TRUE;
}
static void InitFormControl() {
	g_member = InitCardManager();
	SetDlgItemText(g_hDlg, IDC_MEMBERNAMEEDIT, "请输入姓名");
	SetDlgItemText(g_hDlg, IDC_MEMBERPHONE, "请输入电话");
	SetDlgItemText(g_hDlg, IDC_MEMBERADDR, "请输入住址");
	char buff[1024] = { 0 };
	sprintf(buff, "%u", g_member->m_uID);
	SetDlgItemText(g_hDlg, IDC_MEMBERID, buff);
	SendMessage(GetDlgItem(g_hDlg, IDC_GANDERSELECT), CB_ADDSTRING, 0, "男");
	SendMessage(GetDlgItem(g_hDlg, IDC_GANDERSELECT), CB_ADDSTRING, 0, "女");
	SendMessage(GetDlgItem(g_hDlg, IDC_GANDERSELECT), CB_ADDSTRING, 0, "未知");
	SendMessage(GetDlgItem(g_hDlg, IDC_GANDERSELECT), CB_SETCURSEL, (WPARAM)2, (LPARAM)0);

}
static void SaveMember() {
	GetDlgItemText(g_hDlg, IDC_MEMBERNAMEEDIT, g_member->m_szName, 512);
	GetDlgItemText(g_hDlg, IDC_MEMBERPHONE, g_member->m_szPhone, 512);
	GetDlgItemText(g_hDlg, IDC_MEMBERADDR, g_member->m_szAddress, 512);
	//GetDlgItemText(g_hDlg, IDC_GANDERSELECT, g_member->m_szName, 512);

	SignUpCard(g_member);
	SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	MessageBox(NULL, "保存成功！", "提示", MB_OK);
	PostMessage(g_hDlg, WM_CLOSE, 0, 0); // 发送关闭消息给窗口
}
INT_PTR CALLBACK AddMemberFormCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG: {
		g_hDlg = hDlg;
		InitFormControl();
		SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case(IDC_MEMBERADDBUTTON): {
			SaveMember();
			break;
		}
		case(IDCANCEL): {
			SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		default:
			break;
		}
		if (CBN_SELCHANGE == HIWORD(wParam) && GetDlgItem(g_hDlg, IDC_GANDERSELECT) == (HWND)lParam) {
			int selectedIndex = SendMessage(GetDlgItem(g_hDlg, IDC_GANDERSELECT), CB_GETCURSEL, 0, 0);
			g_member->m_Gander = selectedIndex;
		}
		break;
	}

	case WM_NOTIFY: {
		OnNotify(g_hDlg, (NMHDR*)lParam);
		break;
	}

	}
	return (INT_PTR)FALSE;
}
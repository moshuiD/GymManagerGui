#include "AddMemberBodyInfoForm.h"
static HWND g_hDlg = NULL;
static Member* g_member = NULL;
static int g_selectMemberIndex = -1; 
BodyInfo g_BodyData;
static void InitFormControl() {
	GetMember(g_selectMemberIndex, &g_member);
	SetDlgItemText(g_hDlg, IDC_HEIGHTBOX, "请输入身高信息（厘米）");
	SetDlgItemText(g_hDlg, IDC_WEIGHT, "请输入体重信息（千克）");
	SetDlgItemText(g_hDlg, IDC_FAT, "请输入体脂信息");
}
static void AddMemberInfo() {
	char buff[64] = { 0 };
	GetDlgItemText(g_hDlg, IDC_HEIGHTBOX, buff, 64);
	sscanf(buff, "%u", &g_BodyData.m_uHeight);
	GetDlgItemText(g_hDlg, IDC_WEIGHT, buff, 64);
	sscanf(buff, "%u", &g_BodyData.m_uWeight);
	GetDlgItemText(g_hDlg, IDC_FAT, buff, 64);
	sscanf(buff, "%f", &g_BodyData.m_fFat);
}
INT_PTR CALLBACK AddMemberBodyInfoFormCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG: {
		g_hDlg = hDlg;
		g_selectMemberIndex = *(int*)lParam;
		InitFormControl();
		char buff[64] = { 0 };
		sprintf(buff, "添加身体信息-卡号: %u", g_member->m_uID);
		SetWindowText(g_hDlg, buff);
		SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case(IDC_MEMBERBODYINFOBUTTON): {
			AddMemberInfo();
			PostMessage(g_hDlg, WM_CLOSE, 0, 0);
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

		break;
	}

	case WM_NOTIFY: {
		//OnNotify(g_hDlg, (NMHDR*)lParam);
		break;
	}

	}
	return (INT_PTR)FALSE;
}
#include "MemberBodyInfoForm.h"
static HWND g_hDlg = NULL;
static HWND g_hList = NULL;
static void InitFormControl() {
	LVCOLUMN vcl;
	vcl.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	vcl.pszText = "时间";
	vcl.cx = 90;
	vcl.iSubItem = 0;
	ListView_InsertColumn(g_hList, 0, &vcl);
	vcl.pszText = "身高";
	vcl.cx = 70;
	vcl.iSubItem = 1;
	ListView_InsertColumn(g_hList, 1, &vcl);
	vcl.pszText = "体重";
	vcl.cx = 70;
	vcl.iSubItem = 2;
	ListView_InsertColumn(g_hList, 2, &vcl);
	vcl.pszText = "体脂";
	vcl.cx = 70;
	vcl.iSubItem = 3;
	ListView_InsertColumn(g_hList, 3, &vcl);
	
}
INT_PTR CALLBACK MemberBodyInfoCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG: {
		g_hDlg = hDlg;
		g_hList = GetDlgItem(g_hDlg, IDC_MEMBERBODYLIST);
		InitFormControl();
		SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		
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
#include "RechargeForm.h"
static HWND g_hDlg = NULL;
static int g_selectIndex = 0;
static 	Member* g_mem = NULL;
INT_PTR CALLBACK RechargeFormCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG: {
		g_hDlg = hDlg;
		g_selectIndex = *(int*)lParam;
		SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	
		GetMember(g_selectIndex, &g_mem);
		char buff[128] = { 0 };
		sprintf(buff, "����ֵ-����:%u ", g_selectIndex);
		SetWindowText(g_hDlg, buff);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case(IDC_RECHARGEOK): {
			
			if (NULL != g_mem) {
				float chargeNum = 0;
				char chargeBuff[128] = { 0 };
				GetDlgItemText(g_hDlg, IDC_RECHARGEEDITBOX, chargeBuff, 128);
				sscanf(chargeBuff, "%f", &chargeNum);
				char buff[128] = {0};
				sprintf(buff, "���������:%u �Ļ�Ա��ֵ:%.2f Ԫ\r\n��Ա������:%.2f Ԫ�����\r\n�Ƿ��ֵ", g_mem->m_uID, chargeNum, g_mem->m_fmoney + chargeNum);
				SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				if (MessageBox(NULL, buff, "��ʾ", MB_OKCANCEL) == IDOK) {
					g_mem->m_fmoney = g_mem->m_fmoney + chargeNum;
					SyncDatabase();
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
			}
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

	}
	return (INT_PTR)FALSE;
}
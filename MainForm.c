#include "MainForm.h"
#include "DataSaveFormat.h"
INT_PTR CALLBACK MainForm(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case(IDC_BOTTON):
			InitDatabase();
			char buff[1024] = {0};
			Member m = {0};
			MemberBodyInfo i = { 0 };
			i.m_fBodyFat = 0.5;
			i.m_szDate = "2023/8/27";
			i.m_uHeight = 190;
			i.m_uWeight = 60;
			m.m_uID = 11111;
			m.m_szName = "111";
			m.m_szPhone = "13167560321";
			m.m_szDateOfBirth = "2004/03/21";
			m.m_szAddress = "11111111";
			m.m_Gander = Female;
			m.m_fmoney = 1000;
			m.m_uAge = 19;
			MemberBodyInfoList l = {0};
			l.m_Next = NULL;
			l.m_data = &i;
			l.m_Begin = &l;
			m.m_BodyInfoList = &l;
			Members2Json(&m, buff);
			Member* m1 = NewMember();
			const char* jsonString = "{\"m_uID\": 11111, \"m_szName\": \"111\", \"m_szDateOfBirth\": \"2004/03/21\", \"m_uAge\": 19, \"m_Gander\": 1, \"m_szAddress\": \"11111111\", \"m_szPhone\": \"13167560321\", \"m_fmoney\": 1000.000000,\"MemberBodyInfo\":[{\"m_szDate\": \"2023/8/27\", \"m_uHeight\": \"190\", \"m_uWeight\": \"60\", \"m_fBodyFat\": 0.500000 },{\"m_szDate\": \"2023/8/28\", \"m_uHeight\": \"190\", \"m_uWeight\": \"60\", \"m_fBodyFat\": 0.500000 },{\"m_szDate\": \"2023/8/29\", \"m_uHeight\": \"190\", \"m_uWeight\": \"60\", \"m_fBodyFat\": 0.500000 },{\"m_szDate\": \"2023/8/30\", \"m_uHeight\": \"190\", \"m_uWeight\": \"60\", \"m_fBodyFat\": 0.500000 }]}";

			Json2Member(jsonString, m1);

			break;
		default:
			break;
		}
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			PostQuitMessage(0);
			return (INT_PTR)TRUE;
		}
	}

	break;
	}
	return (INT_PTR)FALSE;
}
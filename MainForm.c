#include "MainForm.h"
static HWND g_hList = NULL;//List view hwnd
static HWND g_hDlg = NULL;//window hwnd
static int g_MembersSelectedid = -1;

static void UnSelectItem();
static void SetMemberList(Member* mem) {
	LVITEM vitem = { 0 };
	vitem.mask = LVIF_TEXT;
	vitem.pszText = calloc(512, sizeof(char));
	sprintf(vitem.pszText, "%u", mem->m_uID);
	vitem.iItem = 0;
	vitem.iSubItem = 0;
	ListView_InsertItem(g_hList, &vitem);
	free(vitem.pszText);
	vitem.iSubItem = 1;
	vitem.pszText = mem->m_szName;
	ListView_SetItem(g_hList, &vitem);
	vitem.iSubItem = 2;
	vitem.pszText = mem->m_szDateOfBirth;
	ListView_SetItem(g_hList, &vitem);
	vitem.iSubItem = 3;
	vitem.pszText = calloc(512, sizeof(char));
	sprintf(vitem.pszText, "%u", mem->m_uAge);
	ListView_SetItem(g_hList, &vitem);
	free(vitem.pszText);
	vitem.iSubItem = 4;
	vitem.pszText = mem->m_Gander == Female ? "女" : "男";
	ListView_SetItem(g_hList, &vitem);
	vitem.iSubItem = 5;
	vitem.pszText = mem->m_szAddress;
	ListView_SetItem(g_hList, &vitem);
	vitem.iSubItem = 6;
	vitem.pszText = mem->m_szPhone;
	ListView_SetItem(g_hList, &vitem);
	vitem.iSubItem = 7;
	vitem.pszText = calloc(512, sizeof(char));
	sprintf(vitem.pszText, "%.2f", mem->m_fmoney);
	ListView_SetItem(g_hList, &vitem);
	free(vitem.pszText);
	vitem.iSubItem = 8;
	vitem.pszText = mem->m_State == In ? "健身中" : "已离开";
	ListView_SetItem(g_hList, &vitem);
	vitem.iSubItem = 9;
	vitem.pszText = mem->m_Time.m_szInTime;
	ListView_SetItem(g_hList, &vitem);
}
static void RefreshMemberList() {
	ListView_DeleteAllItems(g_hList);
	UnSelectItem();
	LVITEM vitem = { 0 };
	vitem.mask = LVIF_TEXT;
	MemberNode* member = NULL;
	int i = 0;
	for (int state = ListFirst(GetMembers(), &member); STATE_SUCCESS == state; state = ListNext(member, &member)) {
		Member* mem = member->m_data;
		if (IsBadReadPtr(mem, sizeof(mem))) {
			return -1;
		}
		vitem.pszText = calloc(512, sizeof(char));
		sprintf(vitem.pszText, "%u", mem->m_uID);
		vitem.iItem = i;
		vitem.iSubItem = 0;
		ListView_InsertItem(g_hList, &vitem);
		free(vitem.pszText);
		vitem.iSubItem = 1;
		vitem.pszText = mem->m_szName;
		ListView_SetItem(g_hList, &vitem);
		vitem.iSubItem = 2;
		vitem.pszText = mem->m_szDateOfBirth;
		ListView_SetItem(g_hList, &vitem);
		vitem.iSubItem = 3;
		vitem.pszText = calloc(512, sizeof(char));
		sprintf(vitem.pszText, "%u", mem->m_uAge);
		ListView_SetItem(g_hList, &vitem);
		free(vitem.pszText);
		vitem.iSubItem = 4;
		vitem.pszText = mem->m_Gander == Female ? "女" : "男";
		ListView_SetItem(g_hList, &vitem);
		vitem.iSubItem = 5;
		vitem.pszText = mem->m_szAddress;
		ListView_SetItem(g_hList, &vitem);
		vitem.iSubItem = 6;
		vitem.pszText = mem->m_szPhone;
		ListView_SetItem(g_hList, &vitem);
		vitem.iSubItem = 7;
		vitem.pszText = calloc(512, sizeof(char));
		sprintf(vitem.pszText, "%.2f", mem->m_fmoney);
		ListView_SetItem(g_hList, &vitem);
		free(vitem.pszText);
		vitem.iSubItem = 8;
		vitem.pszText = mem->m_State == In ? "健身中" : "已离开";
		ListView_SetItem(g_hList, &vitem);
		vitem.iSubItem = 9;
		vitem.pszText = mem->m_Time.m_szInTime;
		ListView_SetItem(g_hList, &vitem);
		i++;
	}
}
static int InitMemberList() {

	LVCOLUMN vcl;
	vcl.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	vcl.pszText = "卡号";
	vcl.cx = 60;
	vcl.iSubItem = 0;
	ListView_InsertColumn(g_hList, 0, &vcl);
	vcl.pszText = "姓名";
	vcl.cx = 90;
	vcl.iSubItem = 1;
	ListView_InsertColumn(g_hList, 1, &vcl);
	vcl.pszText = "生日";
	vcl.cx = 90;
	vcl.iSubItem = 2;
	ListView_InsertColumn(g_hList, 2, &vcl);
	vcl.pszText = "年龄";
	vcl.cx = 60;
	vcl.iSubItem = 3;
	ListView_InsertColumn(g_hList, 3, &vcl);
	vcl.pszText = "性别";
	vcl.cx = 50;
	vcl.iSubItem = 4;
	ListView_InsertColumn(g_hList, 4, &vcl);
	vcl.pszText = "住址";
	vcl.cx = 180;
	vcl.iSubItem = 5;
	ListView_InsertColumn(g_hList, 5, &vcl);
	vcl.pszText = "手机号";
	vcl.cx = 100;
	vcl.iSubItem = 6;
	ListView_InsertColumn(g_hList, 6, &vcl);
	vcl.pszText = "余额";
	vcl.cx = 60;
	vcl.iSubItem = 7;
	ListView_InsertColumn(g_hList, 7, &vcl);
	vcl.pszText = "会员状态";
	vcl.cx = 60;
	vcl.iSubItem = 8;
	ListView_InsertColumn(g_hList, 8, &vcl);
	vcl.pszText = "进入/离开健身房时间";
	vcl.cx = 120;
	vcl.iSubItem = 9;
	ListView_InsertColumn(g_hList, 9, &vcl);
}
static void SeleteItem(LPNMLISTVIEW lpNMLV) {
	LVITEM seleteItem = { 0 };
	seleteItem.mask = LVIF_TEXT;
	seleteItem.iItem = lpNMLV->iItem;
	char idBuff[12] = "-1";
	seleteItem.pszText = idBuff;
	seleteItem.cchTextMax = sizeof(idBuff);
	ListView_GetItem(g_hList, &seleteItem);
	g_MembersSelectedid = atoi(seleteItem.pszText);
	char buff[48] = "当前用户ID为: ";
	strcat(buff, idBuff);
	SetDlgItemText(g_hDlg, IDC_SELETEID, buff);
	//OutputDebugString(buffer);
	EnableWindow(GetDlgItem(g_hDlg, IDC_DELETEMEMBER), TRUE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_RECHARGE), TRUE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_ENTRY), TRUE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_LEAVE), TRUE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_ADDMEMBERBODYINFO), TRUE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_SHOWBODYINFO), TRUE);
}
static void UnSelectItem() {
	g_MembersSelectedid = -1;
	char buff[48] = "当前用户ID为: ";
	SetDlgItemText(g_hDlg, IDC_SELETEID, buff);
	EnableWindow(GetDlgItem(g_hDlg, IDC_DELETEMEMBER), FALSE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_RECHARGE), FALSE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_ENTRY), FALSE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_LEAVE), FALSE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_ADDMEMBERBODYINFO), FALSE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_SHOWBODYINFO), FALSE);
}
static LRESULT OnNotify(HWND hWnd, NMHDR* lParam)
{
	if (IDC_MEMBERLIST == lParam->idFrom)
	{
		if (LVN_ITEMCHANGED == lParam->code)
		{
			LPNMLISTVIEW pNMLV = (LPNMLISTVIEW)lParam;
			if ((pNMLV->uChanged & LVIF_STATE) && (pNMLV->uNewState & LVIS_SELECTED)) {
				SeleteItem(pNMLV);
			}
			if ((pNMLV->uChanged & LVIF_STATE) && !(pNMLV->uNewState & LVIS_SELECTED)) {	//if not selected
				UnSelectItem();
			}
		}
	}
	return TRUE;
}

INT_PTR CALLBACK MainFormCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG: {
		g_hDlg = hDlg;
		InitDatabase();
		g_hList = GetDlgItem(g_hDlg, IDC_MEMBERLIST);

		InitMemberList();
		RefreshMemberList();
		UnSelectItem();
		HFONT hFont = CreateFont(
			20,//size of font
			0, 0, 0,
			FW_NORMAL,
			FALSE,
			FALSE,
			FALSE,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			"SIMHEI");
		SendMessage(GetDlgItem(g_hDlg, IDC_SEARCHEDIT), WM_SETFONT, (WPARAM)hFont, TRUE);
		SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		if (0 == wmEvent) {
			switch (wmId)
			{
			case(IDC_BOTTON): {
				break;
			}
							//Add Member
			case(IDC_ADDMEMBER): {
				SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_AddMemberForm), g_hDlg, AddMemberFormCallBack);
				//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), g_hDlg, DIALOG2);
				SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				RefreshMemberList();
				break;
			}
							   //Search 
			case(IDC_SEARCHBUTTON): {
				char buff[512] = "-1";
				GetDlgItemText(g_hDlg, IDC_SEARCHEDIT, buff, 512);
				int id = 0;
				sscanf(buff, "%d", &id);
				Member* mem = NULL;
				GetMember(id, &mem);
				if (NULL != mem) {
					ListView_DeleteAllItems(g_hList);
					SetMemberList(mem);
				}
				else {
					SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					MessageBox(NULL, "未找到此会员", "错误", MB_OK);
					SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				}
				break;
			}
			case(IDC_RESETLISTBUTTON): {
				SetDlgItemText(g_hDlg, IDC_SEARCHEDIT, "");
				RefreshMemberList();
				break;
			}
			case(IDC_DELETEMEMBER): {
				SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				char buff[64] = { 0 };
				sprintf(buff, "将要删除用户 %u\r\n操作不可逆，是否继续？", g_MembersSelectedid);
				if (IDOK == MessageBox(NULL, buff, "提示", MB_OKCANCEL)) {
					DeleteCard(g_MembersSelectedid);
					RefreshMemberList();
					MessageBox(NULL, "删除成功！", "提示", MB_OK);
				}
				SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				break;
			}
			case(IDC_RECHARGE): {
				SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_RechargeForm), g_hDlg, RechargeFormCallBack, &g_MembersSelectedid);
				SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				RefreshMemberList();
				break;
			}
			case(IDC_ENTRY): {
				SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				if (EnterGym(g_MembersSelectedid)==STATE_SUCCESS) {
					MessageBox(NULL, "进入成功！", "提示", MB_OK);
					RefreshMemberList();
				}
				else {
					MessageBox(NULL, "会员已进入！", "错误", MB_OK);
				}
				SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				break;
			}
			case(IDC_LEAVE): {
				SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				switch (LeaveGym(g_MembersSelectedid))
				{
				case(STATE_SUCCESS): {
					MessageBox(NULL, "离开成功！", "提示", MB_OK);
					RefreshMemberList();
					break;
				}
				case(AccessManager_NotEnoughMoney): {
					MessageBox(NULL, "余额不足！\r\n请充值", "错误", MB_OK);
					break;
				}
				case(AccessManager_MemberNotEnter): {
					MessageBox(NULL, "会员不在健身房内！", "错误", MB_OK);
					break;
				}
				default:
					break;
				}
				SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				break;
			}
			case(IDC_SHOWBODYINFO): {
				SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_MemberBodyInfoForm), g_hDlg, MemberBodyInfoCallBack, &g_MembersSelectedid);
				SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				break;
			}
			case(IDC_ADDMEMBERBODYINFO): {
				SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				Member* mem = NULL;
				GetMember(g_MembersSelectedid, &mem);
				if (In != mem->m_State) {
					MessageBox(NULL, "会员未进入健身房！", "错误", MB_OK);
					SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					break;
				}
				DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_AddMemberBodyInfoForm), g_hDlg, AddMemberBodyInfoFormCallBack, &g_MembersSelectedid);
				//add memberBodyInfo.
				switch (AddMemberBodyInfo(g_MembersSelectedid, g_BodyData.m_uHeight, g_BodyData.m_uWeight, g_BodyData.m_fFat))
				{
				case(AccessManager_MemberInfoListFilled): {
					SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					MessageBox(NULL, "新增错误，列表已满！", "错误", MB_OK);
					SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					break;
				}
				case(STATE_SUCCESS): {
					SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					MessageBox(NULL, "添加成功！", "信息", MB_OK);
					break;
				}
				default:
					break;
				}

				SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				RefreshMemberList(); 
				break;
			}
			default:
				break;
			}
		}
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			PostQuitMessage(0);
			return (INT_PTR)TRUE;
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
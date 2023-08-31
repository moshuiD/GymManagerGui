#include "MemberBodyInfoForm.h"
static HWND g_hDlg = NULL;
static HWND g_hList = NULL;
static char g_seleteDate[24] = { 0 };
static int g_seleteMemberId = -1;
static Member* g_member = NULL;
static void UnSelectItem();
static void InitFormControl() {

	GetMember(g_seleteMemberId, &g_member);
	LVCOLUMN vcl;
	vcl.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	vcl.pszText = "时间";
	vcl.cx = 120;
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
static void RefreshMemberList() {
	ListView_DeleteAllItems(g_hList);
	UnSelectItem();
	LVITEM vitem = { 0 };
	vitem.mask = LVIF_TEXT;
	MemberBodyInfoList* bodyInfoNode = g_member->m_BodyInfoList;
	int i = 0;
	for (int state = ListFirst(bodyInfoNode->m_Begin, &bodyInfoNode); STATE_SUCCESS == state; state = ListNext(bodyInfoNode, &bodyInfoNode)) {
		MemberBodyInfo* memberInfo = bodyInfoNode->m_data;
		if (IsBadReadPtr(memberInfo, sizeof(MemberBodyInfo))) {
			return -1;
		}
		vitem.pszText = memberInfo->m_szDate;
		vitem.iItem = i;
		vitem.iSubItem = 0;
		ListView_InsertItem(g_hList, &vitem);
		vitem.pszText = calloc(512, sizeof(char));
		vitem.iSubItem = 1;
		sprintf(vitem.pszText, "%u", memberInfo->m_uHeight);
		ListView_SetItem(g_hList, &vitem);
		vitem.iSubItem = 2;
		sprintf(vitem.pszText, "%u", memberInfo->m_uWeight);
		ListView_SetItem(g_hList, &vitem);
		vitem.iSubItem = 3;
		sprintf(vitem.pszText, "%.2f", memberInfo->m_fBodyFat);
		ListView_SetItem(g_hList, &vitem);
		free(vitem.pszText);
		i++;
	}
}
static void SeleteItem(LPNMLISTVIEW lpNMLV) {
	LVITEM seleteItem = { 0 };
	seleteItem.mask = LVIF_TEXT;
	seleteItem.iItem = lpNMLV->iItem;
	char dateBuff[24] = "-1";
	seleteItem.pszText = dateBuff;
	seleteItem.cchTextMax = sizeof(dateBuff);
	ListView_GetItem(g_hList, &seleteItem);
	strcpy(g_seleteDate, seleteItem.pszText);
	EnableWindow(GetDlgItem(g_hDlg, IDC_DELETEBODYINFOBUTTON), TRUE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_REPLACEMAMBERINFO2), TRUE);
}
static void UnSelectItem() {
	strcpy(g_seleteDate , "-1");
	EnableWindow(GetDlgItem(g_hDlg, IDC_DELETEBODYINFOBUTTON), FALSE);
	EnableWindow(GetDlgItem(g_hDlg, IDC_REPLACEMAMBERINFO2), FALSE);

}
static LRESULT OnNotify(HWND hWnd, NMHDR* lParam)
{
	if (IDC_MEMBERBODYLIST == lParam->idFrom)
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

INT_PTR CALLBACK MemberBodyInfoCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG: {
		g_hDlg = hDlg;
		g_hList = GetDlgItem(g_hDlg, IDC_MEMBERBODYLIST);
		g_seleteMemberId = *(int*)lParam;
		InitFormControl();
		RefreshMemberList();
		char buff[64] = { 0 };
		sprintf(buff, "卡号: %u 的身体信息", g_member->m_uID);
		SetWindowText(g_hDlg, buff);
		UnSelectItem();
		SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case(IDC_DELETEBODYINFOBUTTON): {
			int i = 0;
			MemberBodyInfoNode* bodyInfoNode = NULL;
			for (int state = ListFirst(g_member->m_BodyInfoList->m_Begin, &bodyInfoNode); STATE_SUCCESS == state; state = ListNext(bodyInfoNode, &bodyInfoNode)) {
				MemberBodyInfo* memberInfo = bodyInfoNode->m_data;
				if (IsBadReadPtr(memberInfo, sizeof(MemberBodyInfo))) {
					bodyInfoNode = NULL;
					break;
				}
				if (-1 == g_seleteMemberId) {
					break;
				}
				i++;
			}
			if (NULL != bodyInfoNode) {
				FreeMemberBodyInfo(erase(bodyInfoNode));
				SyncDatabase();
				RefreshMemberList();
				SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				MessageBox(NULL, "删除成功！", "提示", MB_OK);
				SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
			break;
		}
		case(IDC_ADDMEMBERINFO): {
			SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			if (In != g_member->m_State) {
				MessageBox(NULL, "会员未进入健身房！", "错误", MB_OK);
				SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				break;
			}
			DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_AddMemberBodyInfoForm), g_hDlg, AddMemberBodyInfoFormCallBack, &g_member->m_uID);
			//add memberBodyInfo.
			switch (AddMemberBodyInfo(g_member->m_uID,g_BodyData.m_uHeight, g_BodyData.m_uWeight,g_BodyData.m_fFat))
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
		case(IDC_REPLACEMAMBERINFO2): {
			SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_AddMemberBodyInfoForm), g_hDlg, AddMemberBodyInfoFormCallBack, &g_member->m_uID);
			MemberBodyInfo* memData = NewMemberBodyInfo();
			//construct a new MemberBodyInfo
			time_t currentTime;
			struct tm* info;
			time(&currentTime);
			info = localtime(&currentTime);
			strftime(memData->m_szDate, 512, "%Y-%m-%d %H:%M:%S", info);
			memData->m_uHeight = g_BodyData.m_uHeight;
			memData->m_uWeight = g_BodyData.m_uWeight;
			memData->m_fBodyFat = g_BodyData.m_fFat;
			//
			if (ReplaceBodyInfo(g_member, g_seleteDate, memData) == STATE_SUCCESS) {
				SetWindowPos(g_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				RefreshMemberList();
				MessageBox(NULL, "修改成功！", "提示", MB_OK);
				SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}

			SetWindowPos(g_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
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
		OnNotify(g_hDlg, (NMHDR*)lParam);
		break;
	}

	}
	return (INT_PTR)FALSE;
}
// dlg1.cpp: 实现文件
//

#include "pch.h"
#include "DD.h"
#include "dlg1.h"
#include "afxdialogex.h"
#include "WorkThread.h"
#include "DDDlg.h"
#include "VMProtectSDK.h"
#include "clouds.h"
// dlg1 对话框

IMPLEMENT_DYNAMIC(dlg1, CDialogEx)

dlg1::dlg1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

dlg1::~dlg1()
{
}

void dlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_AccountList);
	DDX_Control(pDX, IDC_EDIT1, m_EditGamePath);
	DDX_Control(pDX, IDC_EDIT2, m_EditMachineName);
}


BEGIN_MESSAGE_MAP(dlg1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON5, &dlg1::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &dlg1::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &dlg1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &dlg1::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_CHECK2, &dlg1::OnBnClickedCheck2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &dlg1::OnNMRClickList2)
	ON_COMMAND(ID_32771, &dlg1::On32771)
	ON_COMMAND(ID_0_32772, &dlg1::On032772)
	ON_BN_CLICKED(IDC_BUTTON2, &dlg1::OnBnClickedButton2)
END_MESSAGE_MAP()


// dlg1 消息处理程序


void dlg1::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString GamePath;

	BROWSEINFO bi;
	char Buffer[MAX_PATH];

	//初始化入口参数 bi
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;
	bi.lpszTitle = _T("游戏路径选择");
	bi.ulFlags = BIF_EDITBOX;
	bi.lpfn = NULL;
	bi.iImage = IDR_MAINFRAME;

	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi); //调用显示选择对话框 
												   //注意下 这个函数会分配内存 单不会释放 需要手动释放

	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		//取得文件夹路径放置Buffer空间
		GamePath = Buffer; //将文件夹路径保存在CString 对象里面
	}

	CoTaskMemFree(pIDList);

	if (GamePath.IsEmpty()) {
		MessageBox(_T("请选择正确游戏路径"), _T("提示"));
		return;
	}

	SetDlgItemText(IDC_EDIT1, GamePath + "\\Bin\\Game.exe");
}


void dlg1::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString			RootPath;
	CString			Data;
	CString			Index;
	CStringArray	SplitStr;
	CStdioFile		myFile;

	char ExePath[MAX_PATH];


	GetCurrentDirectory(MAX_PATH, ExePath);
	RootPath = ExePath;
	TCHAR szFilter[] = _T("账号文件(*.ini;*.txt)||文本文件(*.txt)||所有文件(*.*)||");//设置过滤器，双竖线结尾，单竖线隔开；
	CFileDialog fileDlg(TRUE, _T("txt"), RootPath+"\\", 0, szFilter, this);   // 构造打开文件对话框，第一个参数为false表示构造另存为对话框  
	if (IDOK == fileDlg.DoModal())    // 显示打开文件对话框
	{
		if (!myFile.Open(fileDlg.GetPathName(), CFile::modeRead | CFile::shareDenyRead, NULL))
		{
			MessageBox(_T("文件打开失败，请检查文件类型是否正确"), _T(""));
			myFile.Close();
			return;
		}

		while (myFile.ReadString(Data))
		{
			if ("" == Data)
			{
				break;
			}
			TRACE("获取账号：%s\n", Data);

			if (Data.Find("----") > -1 || Data.Find("格式") > -1 || Data.Find("举例") > -1)
			{
				continue;
			}

			SplitCStringArr(Data, "|", &SplitStr);

			if (SplitStr.GetCount() >= 4) {
				TRACE("账号=%s,密码=%s,角色位置=%s,服务器=%s\n", SplitStr.GetAt(0), SplitStr.GetAt(1), SplitStr.GetAt(2), SplitStr.GetAt(3));
				int n = m_AccountList.GetItemCount();
				m_AccountList.InsertItem(n, NULL);
				Index.Format(_T("%d"), n + 1);
				m_AccountList.SetItemText(n, 0, Index);					//加入编号
				m_AccountList.SetItemText(n, 1, SplitStr.GetAt(0));		//加入账号
				m_AccountList.SetItemText(n, 2, SplitStr.GetAt(1));		//加入密码
				m_AccountList.SetItemText(n, 3, SplitStr.GetAt(2));		//加入角色位置
				m_AccountList.SetItemText(n, 4, SplitStr.GetAt(3));		//加入服务器
				SplitStr.RemoveAll();
			}
		}
	}

	
}


bool dlg1::SplitCStringArr(CString expression, CString delimiter, CStringArray* resultArr)
{
	int pos = 0;
	int pre_pos = 0;
	TRACE("待分割数据:%s 分隔符:%s\n", expression, delimiter);
	if (expression.IsEmpty()) {
		return false;
	}
	/*pos = expression.Find(delimiter, (pos + 1));*/
	while (true)
	{
		pos = expression.Find(delimiter, 0);
		if (-1 == pos) {
			(*resultArr).Add(expression);
			TRACE("分割结果:%s\n", expression);
			break;
		}
		else {
			(*resultArr).Add(expression.Mid(pre_pos, (pos - pre_pos)));
			TRACE("分割结果:%s\n", expression.Mid(pre_pos, (pos - pre_pos)));
			expression.Delete(0, pos - pre_pos + 1);
		}
	}
	//resultArr = PosArr;
	return true;
}

BOOL dlg1::PreTranslateMessage(MSG* pMsg)
{
	//屏蔽ESC关闭窗体/
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	//屏蔽回车关闭窗体,但会导致回车在窗体上失效.
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN && pMsg->wParam) return TRUE;
	else
		return CDialog::PreTranslateMessage(pMsg);
}

bool dlg1::Start()
{
	InitData();			//初始化运行数据

	m_WorkThread = (HANDLE)_beginthreadex(NULL, NULL, WorkThread,(LPVOID)AfxGetMainWnd(), 0, NULL);
	if (NULL == m_WorkThread) {
		MessageBox(_T("创建线程失败,请联系代理反馈!"));
		return false;
	}
	else {
		TRACE("工作线程创建成功\n");
		m_WorkThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		//CloseHandle(mWorkThread);
		return true;
	}
}

bool dlg1::Stop()
{
	SetEvent(m_WorkThreadEvent);
	return false;
}

void dlg1::InitData()
{
	m_EditGamePath.GetWindowTextA(m_GamePath);
}

void dlg1::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//启动游戏
}


void dlg1::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//启动选中项
	VMProtectBeginUltra("start");
	CString data = JData();
	if ("2FB1C5CF58867B5BBC9A1B145A86F3A0" == data)
	{
		Start(); 
	}
	else {
		exit(0);
	}

	VMProtectEnd();
}


void dlg1::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditMachineName.GetWindowTextA(m_MyClientSoket.m_MachineName);		//获取机器id
	if (m_MyClientSoket.MyStart()) {
		TRACE("连接中控中");
	}
}


void dlg1::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDDDlg* dlg = (CDDDlg*)AfxGetMainWnd();
	if (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck()) {
		dlg->InitControlThread();
	}
	else {
		dlg->StopControlThread();
	}
}


void dlg1::OnNMRClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//获取鼠标坐标
	CPoint ptCurSel(0, 0);
	GetCursorPos(&ptCurSel);
	//转换为当前控件坐标系的坐标
	m_AccountList.ScreenToClient(&ptCurSel);
	LVHITTESTINFO HitTestInfo;
	HitTestInfo.pt = ptCurSel;
	//判断坐标命中第几项
	int nItem = m_AccountList.HitTest(&HitTestInfo);

	//如果有选中项
	if (nItem != -1)
	{
		//读取选中项内容
		char szTmp[MAX_PATH];
		m_AccountList.GetItemText(nItem, 0, szTmp, MAX_PATH);
		DWORD dwThreadID = strtoul(szTmp, NULL, 10);

		//HMODULE hDll = LoadLibrary("Kernel32.dll");
		//_OPENTHREAD OpenThread = (_OPENTHREAD)GetProcAddress(hDll, "OpenThread");
		//m_hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, dwThreadID);

			//弹出菜单
		CMenu menu;
		menu.LoadMenu(IDR_MENU1);
		CPoint point;
		GetCursorPos(&point);
		CMenu* pSubMenu = menu.GetSubMenu(0);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}
}


void dlg1::On32771()
{
	// TODO: 在此添加命令处理程序代码
	TRACE("启动脚本");
	CString Text;
	CDDDlg* dlg = (CDDDlg*)AfxGetMainWnd();
	int n = m_AccountList.GetNextItem(-1, LVIS_SELECTED);
	vector<THREADINFO>::iterator iter;

	for (iter = dlg->RunThread.begin(); iter != dlg->RunThread.end(); iter++)
	{
		Text.Format("%d", iter->GameHwnd);
		if (Text == m_AccountList.GetItemText(n, 5)) {
			if (iter->GameInfoMem != 0) {
				iter->GameInfoMem->ControlId = CONTROL_RESUME;
			}
		}
	}
}


void dlg1::On032772()
{
	// TODO: 在此添加命令处理程序代码
	TRACE("启动脚本");
	CString Text;
	CDDDlg* dlg = (CDDDlg*)AfxGetMainWnd();
	int n = m_AccountList.GetNextItem(-1, LVIS_SELECTED);
	vector<THREADINFO>::iterator iter;

	for (iter = dlg->RunThread.begin(); iter != dlg->RunThread.end(); iter++)
	{
		Text.Format("%d", iter->GameHwnd);
		if (Text == m_AccountList.GetItemText(n, 5)) {
			if (iter->GameInfoMem != 0) {
				iter->GameInfoMem->ControlId = CONTROL_RESUME;
			}
		}
	}
}


void dlg1::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Stop();
}

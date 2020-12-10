
// DDDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DD.h"
#include "DDDlg.h"
#include "afxdialogex.h"
#include "UpdateThread.h"
#include "VMProtectSDK.h"
#include "clouds.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDDDlg 对话框

//————————————状态栏结数组——————————————//
static UINT Indicators[] = {
	IDS_STRING_Ver,
	IDS_STRING_RunTime,
	IDS_STRING_ExpiryTime,
	IDS_STRING_RunState,
};

CDDDlg::CDDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

void CDDDlg::InitTabDlg()
{
	m_tab.InsertItem(0, "运行列表");
	m_tab.InsertItem(1, "脚本设置");

	m_Page1.Create(IDD_DIALOG1, &m_tab);
	m_Page2.Create(IDD_DIALOG2, &m_tab);
	//设定在Tab内显示的范围  
	CRect tabRect;
	m_tab.GetClientRect(tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 22;
	tabRect.bottom -= 1;
	m_Page1.MoveWindow(&tabRect);
	m_Page2.MoveWindow(&tabRect);
	//显示初始页面  
	m_Page1.ShowWindow(SW_SHOW);
	m_Page2.ShowWindow(SW_HIDE);
}

void CDDDlg::InitDlg1List()
{
	//初始化账号列表
	DWORD dwStyle = m_Page1.m_AccountList.GetExtendedStyle();
	dwStyle = LVS_EX_FULLROWSELECT | LVS_AUTOARRANGE | LVS_SORTASCENDING | LVS_EX_GRIDLINES | LVS_OWNERDATA | LVS_OWNERDRAWFIXED | LVS_EX_CHECKBOXES;
	DWORD dwRet = m_Page1.m_AccountList.SetExtendedStyle(dwStyle);

	m_Page1.m_AccountList.InsertColumn(1, _T("编号"), LVCFMT_CENTER, 40);
	//m_Page1.m_AccountList..InsertColumn(2, _T("窗口句柄"), LVCFMT_CENTER, 70);
	m_Page1.m_AccountList.InsertColumn(2, _T("账号"), LVCFMT_CENTER, 80);
	m_Page1.m_AccountList.InsertColumn(3, _T("密码"), LVCFMT_CENTER, 0);
	m_Page1.m_AccountList.InsertColumn(4, _T("位置"), LVCFMT_CENTER, 25);
	m_Page1.m_AccountList.InsertColumn(5, _T("服务器"), LVCFMT_CENTER, 60);
	m_Page1.m_AccountList.InsertColumn(6, _T("窗口"), LVCFMT_CENTER, 80);
	m_Page1.m_AccountList.InsertColumn(7, _T("角色名"), LVCFMT_CENTER, 60);
	m_Page1.m_AccountList.InsertColumn(8, _T("等级"), LVCFMT_CENTER, 25);
	m_Page1.m_AccountList.InsertColumn(9, _T("门派"), LVCFMT_CENTER, 50);
	m_Page1.m_AccountList.InsertColumn(10, _T("组队"), LVCFMT_CENTER, 80);
	m_Page1.m_AccountList.InsertColumn(11, _T("血量"), LVCFMT_CENTER, 50);
	m_Page1.m_AccountList.InsertColumn(12, _T("刷怪"), LVCFMT_CENTER, 0);
	m_Page1.m_AccountList.InsertColumn(13, _T("状态"), LVCFMT_CENTER, 220);

	//初始化选择任务列表
	DWORD dwStyle1 = m_Page2.m_ListTaskSelete.GetExtendedStyle();
	dwStyle1 = LVS_EX_FULLROWSELECT | LVS_AUTOARRANGE | LVS_SORTASCENDING | LVS_EX_GRIDLINES | LVS_OWNERDATA | LVS_OWNERDRAWFIXED ;
	DWORD dwRet1 = m_Page2.m_ListTaskSelete.SetExtendedStyle(dwStyle1);
	m_Page2.m_ListTaskSelete.InsertColumn(1, _T("选择可做任务"), LVCFMT_CENTER, 100);
	m_Page2.m_ListTaskSelete.InsertItem(0, "自动30级");
	m_Page2.m_ListTaskSelete.InsertItem(1, "跑商");
	m_Page2.m_ListTaskSelete.InsertItem(2, "刷马贼");
	m_Page2.m_ListTaskSelete.InsertItem(3, "师门任务");
	m_Page2.m_ListTaskSelete.InsertItem(4, "帮会任务");
	m_Page2.m_ListTaskSelete.InsertItem(5, "定点刷怪");

	//初始化执行任务列表
	DWORD dwStyle2 = m_Page2.m_ListTaskRun.GetExtendedStyle();
	dwStyle2 = LVS_EX_FULLROWSELECT | LVS_AUTOARRANGE | LVS_SORTASCENDING | LVS_EX_GRIDLINES | LVS_OWNERDATA | LVS_OWNERDRAWFIXED;
	DWORD dwRet2 = m_Page2.m_ListTaskRun.SetExtendedStyle(dwStyle2);
	m_Page2.m_ListTaskRun.InsertColumn(1, _T("脚本流程"), LVCFMT_CENTER, 100);
}

void CDDDlg::InitStatusBar()
{
	m_StatusBar.Create(this);
	m_StatusBar.SetIndicators(Indicators, sizeof(Indicators) / sizeof(UINT));

	CRect rect;
	GetClientRect(&rect);

	//设置名栏长度
	m_StatusBar.SetPaneInfo(0, IDS_STRING_Ver, SBPS_STRETCH, 60);;
	m_StatusBar.SetPaneInfo(1, IDS_STRING_RunTime, SBPS_NORMAL, 200);
	m_StatusBar.SetPaneInfo(2, IDS_STRING_ExpiryTime, SBPS_NORMAL, 280);
	m_StatusBar.SetPaneInfo(3, IDS_STRING_RunState, SBPS_NORMAL, 200);
	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, ID_INDICATOR_REC);//自动填充用户区域的窗
}

bool CDDDlg::InitPath()
{
	//获取资源路径
	DWORD Size = GetCurrentDirectoryW(0, NULL);
	wchar_t* TmpPath = new wchar_t[Size];
	memset(TmpPath, 0, Size);
	if (GetCurrentDirectoryW(Size, TmpPath))
	{
		m_Resources = TmpPath;
		m_RootPath = TmpPath;
		m_RegPath = m_RootPath + "\\Reg.ini";
		m_ConfigPath = m_RootPath + "\\Config.ini";
		m_ControlPath = m_RootPath + "\\Server.ini";
		TRACE("基本配置文件:%s\n", m_ConfigPath);
	}
	delete TmpPath;

	return true;
}

bool CDDDlg::InitControlThread()
{
	m_StatusBar.SetPaneText(3, "运行状态:启动中控");
	Sleep(2000);
	m_UpdataControlThread = _beginthreadex(NULL, NULL, _UpdateControlThread, (LPVOID)this, 0, NULL);
	if (NULL == m_UpdataControlThread) {
		MessageBox(_T("创建线程失败,请联系代理反馈!"));
		return false;
	}
	else {
		TRACE("中控更新线程创建成功\n");
		m_UpdataControlThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		//CloseHandle(m_UpdataControlThreadEvent);
		//CloseHandle(m_UpdataControlThread);
		return true;
	}
}

void CDDDlg::Init()
{
	m_StatusBar.SetPaneText(3, "运行状态:正在初始化");
	m_Page1.m_EditMachineName.GetWindowTextA(m_Page1.m_MyClientSoket.m_MachineName);		//获取机器id
	m_Page1.m_MyClientSoket.ADDRESS = m_ServerIp;											//设置中控IP
	m_Reg = "2FB1C5CF58867B5BBC9A1B145A86F3A0";
	m_StatusBar.SetPaneText(3, "运行状态:初始化完成");
}

void CDDDlg::InitRegDlg()
{
	m_pRegDlg = new CDlgReg();
	int reg = m_pRegDlg->DoModal();
	if (!reg) {
		exit(0);
	}
	CString Time = "到期时间:" + m_Times;
	m_StatusBar.SetPaneText(2, Time);
}

bool CDDDlg::StopControlThread()
{
	m_StatusBar.SetPaneText(3, "运行状态:断开中控");
	if (m_UpdataControlThread != NULL) {
		SetEvent(m_UpdataControlThreadEvent);
		CloseHandle(m_UpdataControlThreadEvent);
	}
	
	return false;
}

void CDDDlg::WriteConfig()
{
	CString TempData;
	CString ComboTemp;
	TRACE("保存配置");
	读取下拉框(TempData, (CComboBox *)m_Page2.GetDlgItem(IDC_COMBO_MenPai));
	m_MyConfig.WriteConfigIni("门派", TempData, m_ConfigPath, "基本设置");
	TempData = "";
	读取编辑框(TempData, (CEdit *)m_Page1.GetDlgItem(IDC_EDIT1));
	m_MyConfig.WriteConfigIni("游戏路径", TempData, m_ConfigPath, "基本设置");
	TempData = "";
	读取链表框(TempData, (CListCtrl *)m_Page2.GetDlgItem(IDC_LIST5));
	m_MyConfig.WriteConfigIni("执行脚本", TempData, m_ConfigPath, "基本设置");
	读取多选框(TempData, (CButton*)m_Page1.GetDlgItem(IDC_CHECK2));
	m_MyConfig.WriteConfigIni("使用中控", TempData, m_ConfigPath, "基本设置");

}

void CDDDlg::ReadConfig()
{
	char TempData[MAX_PATH];
	CString ComboTemp;
	m_MyConfig.ReadConfigIni("门派", TempData, m_ConfigPath, "基本设置");
	设置下拉框(TempData, (CComboBox *)m_Page2.GetDlgItem(IDC_COMBO_MenPai));
	m_MyConfig.ReadConfigIni("游戏路径", TempData, m_ConfigPath, "基本设置");
	设置编辑框(TempData, (CEdit *)m_Page1.GetDlgItem(IDC_EDIT1));
	m_MyConfig.ReadConfigIni("使用中控", TempData, m_ConfigPath, "基本设置");
	设置多选框(TempData, (CButton*)m_Page1.GetDlgItem(IDC_CHECK2));
	m_MyConfig.ReadConfigIni("执行脚本", TempData, m_ConfigPath, "基本设置");
	设置链表框(TempData, (CListCtrl *)&m_Page2.m_ListTaskRun);
	m_MyConfig.ReadConfigIni("中控IP", TempData, m_ControlPath, "中控设置");
	m_ServerIp = TempData;
	m_MyConfig.ReadConfigIni("机器编号", TempData, m_ControlPath, "中控设置");
	设置编辑框(TempData, (CEdit*)m_Page1.GetDlgItem(IDC_EDIT2));
	m_MyConfig.ReadConfigIni("注册码", TempData, m_RegPath, "注册码");
	m_RegCode = TempData;

}



BEGIN_MESSAGE_MAP(CDDDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_UpDataStatusBar, OnUpDataStatusBar)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDDDlg::OnTcnSelchangeTab1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDDDlg 消息处理程序

BOOL CDDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	VMProtectBegin("Init");

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	InitTabDlg();

	InitDlg1List();

	InitStatusBar();

	InitPath();	


	VERIFY(1 == InitSkinMagicLib(AfxGetInstanceHandle(), _T("SCRIBBLE"), NULL, NULL));//初始化SkinMagic

	VERIFY(1 == LoadSkinFile(_TEXT("Tusk.smf")));//加载皮肤文件

	VERIFY(1 == SetWindowSkin(this->m_hWnd, TEXT("Dialog")));

	ReadConfig();

	Init();
	
	if (((CButton*)m_Page1.GetDlgItem(IDC_CHECK2))->GetCheck()) {
		InitControlThread();		//启动中控更新线程
	}

	InitRegDlg();

	m_StatusBar.SetPaneText(0, "当前版本:1.0"); //版本号

	VMProtectEnd();
	ShowWindow(SW_SHOW);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDDDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_tab.GetCurSel())
	{
	case 0:
		m_Page1.ShowWindow(SW_SHOW);
		m_Page2.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_Page1.ShowWindow(SW_HIDE);
		m_Page2.ShowWindow(SW_SHOW);
		break;
	default:break;
	}

}

LRESULT CDDDlg::OnUpDataStatusBar(WPARAM wparam, LPARAM lparam)
{
	TRACE(_T("自定义消息\n"));

	CString* Text = (CString*)lparam;

	switch ((int)wparam)
	{
	case 1:	//更新信息
		m_StatusBar.SetPaneText(3, *Text);
		break;
	case 2:	//更新时间
		m_StatusBar.SetPaneText(1, *Text);
		break;
	case 3:	//更新连接信息
		m_StatusBar.SetPaneText(3, *Text);
		break;
	default:
		break;
	}

	return LRESULT();
}


bool CDDDlg::设置下拉框(CString TempData, CComboBox* Res)
{
	CString ComboTemp;
	for (int i = 0; i < Res->GetCount(); i++) {
		Res->GetLBText(i, ComboTemp);
		if (TempData == ComboTemp)
		{
			Res->SetCurSel(i);
		}
	}
	return true;
}

bool CDDDlg::设置编辑框(CString TempData, CEdit* Res)
{
	Res->SetWindowTextA(TempData);
	return true;
}

bool CDDDlg::设置多选框(CString TempData, CButton* Res)
{
	Res->SetCheck(_ttoi(TempData));
	return true;
}

bool CDDDlg::设置单选框(CString TempData, int ResId)
{
	return false;
}

bool CDDDlg::设置链表框(CString TempData, CListCtrl* Res)
{
	CStringArray listText;

	if (!SplitCStringArr(TempData, "|", &listText)) {
		return false;
	}
	for (int i = 0; i < listText.GetCount(); i++)
	{
		int n = Res->GetItemCount();
		Res->InsertItem(n, listText.GetAt(i));
	}

	

	return false;
}

bool CDDDlg::读取编辑框(CString& TempData, CEdit* Res)
{
	Res->GetWindowTextA(TempData);
	return true;
}

bool CDDDlg::读取多选框(CString& TempData, CButton* Res)
{
	if (Res->GetCheck()) {
		TempData = "1";
	}
	else {
		TempData = "0";
	}
	return true;
}

bool CDDDlg::读取下拉框(CString& TempData, CComboBox* Res)
{
	Res->GetLBText(0, TempData);
	return true;
}

bool CDDDlg::读取链表框(CString& TempData, CListCtrl* Res)
{
	for (int i = 0; i < Res->GetItemCount(); i++)
	{
		TempData += Res->GetItemText(i, 0);
		if (i+1 < Res->GetItemCount()) {
			TempData += "|";
		}	
	}
	return false;
}


void CDDDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	WriteConfig();
	CDialogEx::OnClose();
}


bool CDDDlg::SplitCStringArr(CString expression, CString delimiter, CStringArray* resultArr)
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
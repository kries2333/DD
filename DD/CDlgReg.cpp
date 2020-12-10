// CDlgReg.cpp: 实现文件
//

#include "pch.h"
#include "DD.h"
#include "CDlgReg.h"
#include "afxdialogex.h"
#include "clouds.h"
#include "VMProtectSDK.h"
#include "DDDlg.h"

// CDlgReg 对话框

IMPLEMENT_DYNAMIC(CDlgReg, CDialogEx)


CDlgReg::CDlgReg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CDlgReg::~CDlgReg()
{
}

void CDlgReg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CDlgReg::OnInitDialog()
{
	VMProtectBeginUltra("RegInit");
	//LIB初始化开始
	HMODULE  hCallerModule = NULL;
	TCHAR  szModuleName[MAX_PATH] = _T("");
	if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)(void*)&CloudS_DllMain, &hCallerModule))
	{
		GetModuleFileName(hCallerModule, szModuleName, ARRAYSIZE(szModuleName));
	}
	CloudS_DllMain(GetModuleHandle(szModuleName), DLL_PROCESS_ATTACH, NULL);

	int bareg = Areg(25559, "", "o0oona44ql6qpq4ay8", "1+3+4+", 0);
	if (bareg == 1){
		CString strTmp;
		//strTmp = GetInfo(200);
		//SetDlgItemText(IDC_EDIT_REG, strTmp);
	}
	else
	{
		int bInitialization = Initialization(25559, 1, "o0oona44ql6qpq4ay8", "1+3+4+", 0);
		if (bInitialization)
		{
			CString strTmp;
			strTmp = GetInfo(1);
			SetDlgItemText(IDC_STATIC, strTmp);
		}
	}

	SetDlgItemText(IDC_EDIT1, ((CDDDlg*)AfxGetMainWnd())->m_RegCode);
	VMProtectEnd();
	ShowWindow(SW_SHOW);
	m_ParentDlg = (void*)AfxGetMainWnd();
	_beginthreadex(NULL, NULL, Login, (PVOID)this, 0, NULL);
	return TRUE;
}


BEGIN_MESSAGE_MAP(CDlgReg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgReg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgReg::OnBnClickedButton2)
	ON_MESSAGE(WM_OnCloseMsg, &CDlgReg::OnCloseMsg)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgReg 消息处理程序


void CDlgReg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//注册
	_beginthreadex(NULL, NULL, Login, (PVOID)this, 0, NULL);
}


void CDlgReg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//解绑
	UpdateData(TRUE);
	CString cTemp;
	GetDlgItemText(IDC_EDIT1, cTemp);
	//解绑

	int a = Tie(cTemp.GetBuffer());
	if (1 == a) {
		//ExitProcess(0);
		MessageBox("解绑成功:扣时1天");
		exit(0);
	}
	else {
		cTemp = Tips();
		SetDlgItemText(IDC_STATIC_GongGao, Tips());	//调用失败
	}
}

void CDlgReg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	EndDialog(0);
	CDialogEx::OnClose();
}

LRESULT CDlgReg::OnCloseMsg(WPARAM wparam, LPARAM lparam)
{
	TRACE(_T("自定义消息\n"));

	CString* Text = (CString*)lparam;

	switch ((int)wparam)
	{
	case 0:	//登录失败
		EndDialog(0);
		break;
	case 1:	//登录成功
		EndDialog(1);
		break;
	default:
		break;
	}

	return LRESULT();
}

void CDlgReg::CloseRegWindow()
{
	EndDialog(1);
}

unsigned int __stdcall Login(LPVOID p)
{
	CDlgReg* myDlg = (CDlgReg*)p;
	CDDDlg* myMainDlg = (CDDDlg*)myDlg->m_ParentDlg;
	VMProtectBeginUltra("Reg");
	if (ISreg() == 1) {
		return 0;
	}

	CString cTemp;
	myDlg->GetDlgItemText(IDC_EDIT1, cTemp);
	
	myMainDlg->m_MyConfig.WriteConfigIni("注册码", cTemp, myMainDlg->m_RegPath, "注册码");
	//注册
	int a = Reg(cTemp.GetBuffer());
	if (!a) {
		myDlg->SetDlgItemText(IDC_STATIC_GongGao, Tips());	//调用失败
	}
	else {
		myDlg->SetDlgItemText(IDC_STATIC_GongGao, Tips());
		CString strTmp;
		strTmp = GetInfo(1);
		Sleep(1000);
		myDlg->SetDlgItemText(IDC_STATIC_GongGao, strTmp);
		myMainDlg->m_Times = QTime();
		for (int i = 0; i < 5; i++)
		{
			CString Title;
			Title.Format("窗口%d秒后关闭", 5 - i);
			myDlg->SetWindowText(Title);
			Sleep(1000);
		}
		SendMessage(myDlg->m_hWnd, WM_OnCloseMsg, (WPARAM)1, NULL);
		return 1;
	}
	VMProtectEnd();
	return 0;
}

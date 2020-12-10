
// DDDlg.h: 头文件
//

#pragma once
#include "dlg1.h"
#include "dlg2.h"
#include "CDlgReg.h"
#include "CMyConfig.h"
#include <iostream>
#include <vector>
using namespace std;

#pragma comment(lib,"skin/SkinMagic.lib")//调用皮肤lib  
#pragma comment(lib,"HPSocket_D.lib")//调用HpScoketLib
#include "skin/SkinMagicLib.h" 

#define CONTROL_RUN	99		//运行中
#define CONTROL_RESUME 100	//启动代码
#define CONTROL_SUSPEND 101	//暂停代码


typedef struct _TLGameInfo {
	char Account[30];			//账号 注入器写入
	char Password[30];			//密码 注入器写入
	char Server[30];			//服务器 注入器写入
	char LuaScript[512];		//需要执行的lua脚本 注入器写入
	char Location[20];			//游戏地图位置
	char RoleName[30];			//角色名
	char RoleSects[20];			//角色门派
	char RoleState[256];		//角色执行的任务状态
	int RoleIndex;				//登录角色下标 注入器写入
	int KillCount;				//刷怪数量
	int RoleLv;					//角色等级
	int RoleHp;					//角色血量
	bool IsInject;				//是否已经注入	dll写入
	DWORD ControlId;			//控制标识
}TLGAMEINFO, PTLGAMEINFO;

typedef struct _ThreadInfo {
	bool IsRun;
	CString UserName;
	CString Password;
	CString Server; 
	CString RoleIndex;
	CString LuaScript;
	HWND GameHwnd;
	HANDLE ThreadHandle;
	HANDLE ExitEvent;
	DWORD ThreadId;
	TLGAMEINFO* GameInfoMem;		//共享内存地址
}THREADINFO, PTHREADINFO;


// CDDDlg 对话框
class CDDDlg : public CDialogEx
{
// 构造
public:
	CDDDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	dlg1 m_Page1;
	dlg2 m_Page2;
	CStatusBar		m_StatusBar;					//状态栏控件
	int	m_RunCount;									//正在运行数量

	CMyConfig m_MyConfig;							//配置文件写入读取

	CString m_Resources;
	CString m_RootPath;								//根目录
	CString m_ConfigPath;							//基本设置路径
	CString m_ControlPath;							//中控路径
	CString m_RegPath;								//注册码路径
	CString m_Times;								//到期时间
	CString m_Reg;									//注册状态
	CString	m_RegCode;								//注册码
	CDlgReg* m_pRegDlg;								//注册窗口指针

	CString m_ServerIp;								//中控IP地址
	HANDLE	m_UpdataControlThreadEvent;				//事件
	unsigned int m_UpdataControlThread;				//更新中控线程

	vector<THREADINFO> RunThread;

public:
	void InitTabDlg();			//初始化tab
	void InitDlg1List();		//初始化界面1list
	void InitStatusBar();		//初始化状态栏
	bool InitPath();			//初始化资源路径
	bool InitControlThread();	//初始化中控更新线程
	void Init();				//初始化所有需要用的数据
	void InitRegDlg();			//初始化注册窗口

	bool StopControlThread();	//停止中控更新线程

	void WriteConfig();		//写入配置
	void ReadConfig();		//读取配置

	bool SplitCStringArr(CString expression, CString delimiter, CStringArray* resultArr); //分割字符串

public:
	bool 设置下拉框(CString TempData, CComboBox* Res);
	bool 设置编辑框(CString TempData, CEdit* Res);
	bool 设置多选框(CString TempData, CButton* Res);
	bool 设置单选框(CString TempData, int ResId);
	bool 设置链表框(CString TempData, CListCtrl* Res);

	bool 读取编辑框(CString& TempData, CEdit* Res);
	bool 读取多选框(CString& TempData, CButton* Res);
	bool 读取下拉框(CString& TempData, CComboBox* Res);
	bool 读取链表框(CString& TempData, CListCtrl* Res);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg LRESULT OnUpDataStatusBar(WPARAM wparam, LPARAM lparam);		//更新状态栏响应函数
	afx_msg void OnClose();
};

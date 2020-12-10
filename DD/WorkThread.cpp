#include "pch.h"
#include "WorkThread.h"
#include "UpdateThread.h"
#include "DDDlg.h"
#include "CGame.h"
#include "InjectDll.h"

#include <thread>
#include <TlHelp32.h>

vector<HWND> g_GameHwnd;
int RunWindow = 0;				//在线窗口数

unsigned int __stdcall WorkThread(LPVOID p)
{
	CDDDlg* myDlg = (CDDDlg*)p;     //界面类为参数
	CGame myGame;					//游戏操作
	CTimeSpan NowTimeSpan = NULL;
	CTimeSpan RestartTimeSPan = NULL;
	CTime OldTime = CTime::GetCurrentTime();
	CTime NowTime = CTime::GetCurrentTime();
	CString Text = "";
	THREADINFO RunInfo = { 0 };				//需要操作的账号数据结构
	
	DWORD singleObjRet = 0;			//线程事件返回结果
	HWND NewWindow = 0;				//需要注入的新窗口
	int CheckCount = 0;
	int OpenCount = 0;
	int OpenGameTimeOut = 0;		//打开游戏超时
	int	RunIndex = 0;				//需要操作的下标
	bool IsCloseThread = false;		//是否关闭线程
	bool IsRunWindow = false;		//当前窗口正在运行中


	bool isOpen = false;
	for (int i = 0; i < myDlg->m_Page1.m_AccountList.GetItemCount(); i++)
	{
		if (myDlg->m_Page1.m_AccountList.GetCheck(i)) {
			RunInfo.UserName = myDlg->m_Page1.m_AccountList.GetItemText(i, 1);
			RunInfo.Password = myDlg->m_Page1.m_AccountList.GetItemText(i, 2);
			RunInfo.RoleIndex = myDlg->m_Page1.m_AccountList.GetItemText(i, 3);
			RunInfo.Server = myDlg->m_Page1.m_AccountList.GetItemText(i, 4);
			for (int j = 0; j < myDlg->m_Page2.m_ListTaskRun.GetItemCount(); j++)
			{
				RunInfo.LuaScript += myDlg->m_Page2.m_ListTaskRun.GetItemText(j, 0);
				if (j + 1 < myDlg->m_Page2.m_ListTaskRun.GetItemCount()) {
					RunInfo.LuaScript += "|";
				}
			}
			myDlg->RunThread.push_back(RunInfo);
			CheckCount++;
		}
	}

	if (CheckCount == 0) {
		MessageBox(myDlg->m_hWnd, "请先选择使用的账号", "提示", 0);
		return -1;
	}

	if (CheckCount > 2) {
		MessageBox(myDlg->m_hWnd, "目前仅支持双开", "提示", 0);
		return -1;
	}

	while (true)
	{
		NowTime = CTime::GetCurrentTime();
		NowTimeSpan = CTime::GetCurrentTime() - OldTime;
		Text.Format(_T("%I64d天%ld小时%ld分钟%ld秒"),
			NowTimeSpan.GetDays(),
			NowTimeSpan.GetHours(),
			NowTimeSpan.GetMinutes(),
			NowTimeSpan.GetSeconds());
		RunTime(myDlg, Text);

		singleObjRet = WaitForSingleObject(myDlg->m_Page1.m_WorkThreadEvent, 1000);
		switch (singleObjRet)
		{
		case WAIT_TIMEOUT:
			if (!GameIsRun(myDlg, CheckCount)) {
				if (g_GameHwnd.size() < CheckCount) {	//如果当前运行的进程小于选中数量则运行进程
					if (!isOpen) {
						if (OpenGame(myDlg->m_Page1.m_GamePath)) {
							isOpen = true;
						}//打开游戏进程
					}
					if (OpenGameTimeOut >= 30) {
						isOpen = false;
					}
					Sleep(5000);							//等待15秒窗口打开
					OpenGameTimeOut++;
					continue;
				}
			}
			else {
				TRACE("游戏已打开\n");
				//开始注入dll 并开启数据共享线程
				for (int i = 0; i < myDlg->RunThread.size(); i++)
				{
					myDlg->RunThread.at(i).IsRun = false;
				}
				IsRunWindow = false;
				for (int i = 0; i < g_GameHwnd.size(); i++) {	//遍历窗口 是否是已绑定窗口
					for (int j = 0; j < myDlg->RunThread.size(); j++)
					{
 						if (myDlg->RunThread.at(j).GameHwnd == g_GameHwnd.at(i)) {
							IsRunWindow = true;
							myDlg->RunThread.at(j).IsRun = true;
							break;	//当前窗口运行中
						}
					}
					if (!IsRunWindow) {
						NewWindow = g_GameHwnd.at(i);			//如果遍历到没有绑定的窗口 当做新窗口处理 开始进行绑定
						IsRunWindow = false;
					}
				}

				for (int i = 0; i < myDlg->RunThread.size(); i++)	//遍历线程信息数组 窗口为0就注入 窗口不为0就释放停止线程
				{
					if (NewWindow != 0 && myDlg->RunThread.at(i).GameHwnd == 0)		//如果线程数组的窗口为0  新窗口 开始绑定和注入
					{
						Sleep(1000);
						DWORD dwPID;
						HANDLE UpdateThread;
						DWORD ThreadId;
						UpdateThread = (HANDLE)_beginthreadex(NULL, NULL, _UpdateThread, (LPVOID)myDlg, 0, (unsigned int*)&ThreadId);
						if (NULL == UpdateThread) {
							MessageBox(myDlg->m_hWnd, "创建线程失败,请联系代理反馈!", "提示", 0);
							return 0;
						}
						else {
							myDlg->m_RunCount++;
							myDlg->RunThread.at(i).ThreadId = ThreadId;
							myDlg->RunThread.at(i).GameHwnd = NewWindow;				//绑定窗口句柄
							myDlg->RunThread.at(i).ThreadHandle = UpdateThread;			//绑定线程句柄
							myDlg->RunThread.at(i).ExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	//创建关闭进程的事件
							CloseHandle(UpdateThread);
							//CloseHandle(myDlg->RunThread.at(i).ExitEvent);
							::GetWindowThreadProcessId(NewWindow, &dwPID);	//获取进程ID
							if (!InJectDll(dwPID, "TLDLL.dll")) {
								myDlg->m_RunCount--;			//注入失败关闭线程
								SetEvent(myDlg->RunThread.at(i).ExitEvent);
								myDlg->RunThread.at(i).GameHwnd = 0;
								myDlg->RunThread.at(i).ThreadHandle = 0;
								myDlg->RunThread.at(i).ExitEvent = 0;
								myDlg->RunThread.at(i).GameInfoMem = 0;
								MessageBox(myDlg->m_hWnd, "注入失败, 关闭杀毒软件后重启", "提示", 0);
								return 0;
							}
							isOpen = false;
							NewWindow = 0;
							break;
						}
					}
					if (!myDlg->RunThread.at(i).IsRun && NewWindow != 0 && myDlg->RunThread.at(RunIndex).ThreadHandle != NULL && myDlg->m_RunCount == CheckCount && NewWindow != myDlg->RunThread.at(RunIndex).GameHwnd) {	//窗口崩溃 释放之前窗口的共享内存和线程
						myDlg->m_RunCount--;
						SetEvent(myDlg->RunThread.at(i).ExitEvent);
						myDlg->RunThread.at(i).GameHwnd = 0;
						myDlg->RunThread.at(i).ThreadHandle = 0;
						myDlg->RunThread.at(i).ExitEvent = 0;
						myDlg->RunThread.at(i).GameInfoMem = 0;
						myDlg->RunThread.at(i).ThreadId = 0;
					}
				}
			}
			break;
		default:
			//退出所有线程;
			for (int i = 0; i < myDlg->RunThread.size(); i++) {
				DWORD dwPID;
				::GetWindowThreadProcessId(myDlg->RunThread.at(i).GameHwnd, &dwPID);	//获取进程ID
				UnInJectDll(dwPID, "TLDLL.dll");
				myDlg->m_RunCount--;
				SetEvent(myDlg->RunThread.at(i).ExitEvent);
				myDlg->RunThread.at(i).GameHwnd = 0;
				myDlg->RunThread.at(i).ThreadHandle = 0;
				myDlg->RunThread.at(i).ExitEvent = 0;
				myDlg->RunThread.at(i).GameInfoMem = 0;
				CloseHandle(myDlg->m_Page1.m_WorkThreadEvent);
				myDlg->m_Page1.m_WorkThreadEvent = 0;
			}
			return 0;
		}
		Sleep(2000);
	}
	return 0;
}


void WINAPI RunTime(CDDDlg* dlg, CString Info)
{
	CString Text = "运行时间:";
	Text += Info;
	TRACE(_T("Text\n"));
	::SendMessage(dlg->m_hWnd, WM_UpDataStatusBar, (WPARAM)2, (LPARAM)&Text);
}

void WINAPI CloseMyWindow(CString ProcessName)
{
	if ("" == ProcessName)
	{
		return;
	}
	HANDLE SnapshotHandle;			//创建系统快照	
	HANDLE ColseHandle;				//用于关闭的句柄

	SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  //获得系统快照

	PROCESSENTRY32* info = NULL;				//定义一个PROCESSENTRY32 结构体指针
	info = new PROCESSENTRY32;					//分配内存
	info->dwSize = sizeof(PROCESSENTRY32);		//设置结构成员Size大小

	Process32First(SnapshotHandle, info);			//获取第一个进程
	while (Process32Next(SnapshotHandle, info) != false)		//如果不是最后一句进程继续循环
	{
		/*		if (ColseProcessID == info->th32ProcessID)*/		//判断是不是需要关闭的进程
		if (ProcessName == info->szExeFile)
		{
			ColseHandle = OpenProcess(PROCESS_TERMINATE, false, info->th32ProcessID);			//打开已存在进程返回现有句柄
			TerminateProcess(ColseHandle, 0);													//终结进程
		}
		TRACE(_T("当前进程：%s\n"), info->szExeFile);
	}

	delete info;
}

void CrearThread(CDDDlg* dlg)
{

}

bool OpenGame(CString Path)
{
	CString Command = Path + " -fl";
	TRACE(_T("游戏路径：%s\n"), Path);
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	bool fSuccess = CreateProcess(NULL, Command.GetBuffer(), NULL, NULL,
		FALSE, 0, NULL, Command.Left(Command.GetLength()-12), &si, &pi);
	return fSuccess;
}

bool GameIsRun(CDDDlg* dlg, int RunCount)
{
	g_GameHwnd.clear();
	RunWindow = 0;
	EnumWindows(EnumChildWindowsProc, NULL); //枚举所有窗口
	if (g_GameHwnd.size() > RunWindow){
		RunWindow = g_GameHwnd.size();
		if (dlg->m_RunCount < RunWindow) {
			return true;
		}
		if (dlg->m_RunCount == RunCount && dlg->m_RunCount == RunWindow) {
			return true;
		}
	}
	return false;	
}


BOOL CALLBACK EnumChildWindowsProc(HWND hWnd, LPARAM lParam)
{
	CString GameTitle;
	char WindowTitle[100] = { 0 };
	::GetWindowText(hWnd, WindowTitle, 100);
	GameTitle = WindowTitle;
	if (GameTitle.Find("新天龙八部") > -1) {
		TRACE("当前句柄 %x :%s\n", hWnd, WindowTitle);
		g_GameHwnd.push_back(hWnd);
	}
	return true;
}



#include "pch.h"
#include "WorkThread.h"
#include "UpdateThread.h"
#include "DDDlg.h"
#include "CGame.h"
#include "InjectDll.h"

#include <thread>
#include <TlHelp32.h>

vector<HWND> g_GameHwnd;
int RunWindow = 0;				//���ߴ�����

unsigned int __stdcall WorkThread(LPVOID p)
{
	CDDDlg* myDlg = (CDDDlg*)p;     //������Ϊ����
	CGame myGame;					//��Ϸ����
	CTimeSpan NowTimeSpan = NULL;
	CTimeSpan RestartTimeSPan = NULL;
	CTime OldTime = CTime::GetCurrentTime();
	CTime NowTime = CTime::GetCurrentTime();
	CString Text = "";
	THREADINFO RunInfo = { 0 };				//��Ҫ�������˺����ݽṹ
	
	DWORD singleObjRet = 0;			//�߳��¼����ؽ��
	HWND NewWindow = 0;				//��Ҫע����´���
	int CheckCount = 0;
	int OpenCount = 0;
	int OpenGameTimeOut = 0;		//����Ϸ��ʱ
	int	RunIndex = 0;				//��Ҫ�������±�
	bool IsCloseThread = false;		//�Ƿ�ر��߳�
	bool IsRunWindow = false;		//��ǰ��������������


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
		MessageBox(myDlg->m_hWnd, "����ѡ��ʹ�õ��˺�", "��ʾ", 0);
		return -1;
	}

	if (CheckCount > 2) {
		MessageBox(myDlg->m_hWnd, "Ŀǰ��֧��˫��", "��ʾ", 0);
		return -1;
	}

	while (true)
	{
		NowTime = CTime::GetCurrentTime();
		NowTimeSpan = CTime::GetCurrentTime() - OldTime;
		Text.Format(_T("%I64d��%ldСʱ%ld����%ld��"),
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
				if (g_GameHwnd.size() < CheckCount) {	//�����ǰ���еĽ���С��ѡ�����������н���
					if (!isOpen) {
						if (OpenGame(myDlg->m_Page1.m_GamePath)) {
							isOpen = true;
						}//����Ϸ����
					}
					if (OpenGameTimeOut >= 30) {
						isOpen = false;
					}
					Sleep(5000);							//�ȴ�15�봰�ڴ�
					OpenGameTimeOut++;
					continue;
				}
			}
			else {
				TRACE("��Ϸ�Ѵ�\n");
				//��ʼע��dll ���������ݹ����߳�
				for (int i = 0; i < myDlg->RunThread.size(); i++)
				{
					myDlg->RunThread.at(i).IsRun = false;
				}
				IsRunWindow = false;
				for (int i = 0; i < g_GameHwnd.size(); i++) {	//�������� �Ƿ����Ѱ󶨴���
					for (int j = 0; j < myDlg->RunThread.size(); j++)
					{
 						if (myDlg->RunThread.at(j).GameHwnd == g_GameHwnd.at(i)) {
							IsRunWindow = true;
							myDlg->RunThread.at(j).IsRun = true;
							break;	//��ǰ����������
						}
					}
					if (!IsRunWindow) {
						NewWindow = g_GameHwnd.at(i);			//���������û�а󶨵Ĵ��� �����´��ڴ��� ��ʼ���а�
						IsRunWindow = false;
					}
				}

				for (int i = 0; i < myDlg->RunThread.size(); i++)	//�����߳���Ϣ���� ����Ϊ0��ע�� ���ڲ�Ϊ0���ͷ�ֹͣ�߳�
				{
					if (NewWindow != 0 && myDlg->RunThread.at(i).GameHwnd == 0)		//����߳�����Ĵ���Ϊ0  �´��� ��ʼ�󶨺�ע��
					{
						Sleep(1000);
						DWORD dwPID;
						HANDLE UpdateThread;
						DWORD ThreadId;
						UpdateThread = (HANDLE)_beginthreadex(NULL, NULL, _UpdateThread, (LPVOID)myDlg, 0, (unsigned int*)&ThreadId);
						if (NULL == UpdateThread) {
							MessageBox(myDlg->m_hWnd, "�����߳�ʧ��,����ϵ������!", "��ʾ", 0);
							return 0;
						}
						else {
							myDlg->m_RunCount++;
							myDlg->RunThread.at(i).ThreadId = ThreadId;
							myDlg->RunThread.at(i).GameHwnd = NewWindow;				//�󶨴��ھ��
							myDlg->RunThread.at(i).ThreadHandle = UpdateThread;			//���߳̾��
							myDlg->RunThread.at(i).ExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	//�����رս��̵��¼�
							CloseHandle(UpdateThread);
							//CloseHandle(myDlg->RunThread.at(i).ExitEvent);
							::GetWindowThreadProcessId(NewWindow, &dwPID);	//��ȡ����ID
							if (!InJectDll(dwPID, "TLDLL.dll")) {
								myDlg->m_RunCount--;			//ע��ʧ�ܹر��߳�
								SetEvent(myDlg->RunThread.at(i).ExitEvent);
								myDlg->RunThread.at(i).GameHwnd = 0;
								myDlg->RunThread.at(i).ThreadHandle = 0;
								myDlg->RunThread.at(i).ExitEvent = 0;
								myDlg->RunThread.at(i).GameInfoMem = 0;
								MessageBox(myDlg->m_hWnd, "ע��ʧ��, �ر�ɱ�����������", "��ʾ", 0);
								return 0;
							}
							isOpen = false;
							NewWindow = 0;
							break;
						}
					}
					if (!myDlg->RunThread.at(i).IsRun && NewWindow != 0 && myDlg->RunThread.at(RunIndex).ThreadHandle != NULL && myDlg->m_RunCount == CheckCount && NewWindow != myDlg->RunThread.at(RunIndex).GameHwnd) {	//���ڱ��� �ͷ�֮ǰ���ڵĹ����ڴ���߳�
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
			//�˳������߳�;
			for (int i = 0; i < myDlg->RunThread.size(); i++) {
				DWORD dwPID;
				::GetWindowThreadProcessId(myDlg->RunThread.at(i).GameHwnd, &dwPID);	//��ȡ����ID
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
	CString Text = "����ʱ��:";
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
	HANDLE SnapshotHandle;			//����ϵͳ����	
	HANDLE ColseHandle;				//���ڹرյľ��

	SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  //���ϵͳ����

	PROCESSENTRY32* info = NULL;				//����һ��PROCESSENTRY32 �ṹ��ָ��
	info = new PROCESSENTRY32;					//�����ڴ�
	info->dwSize = sizeof(PROCESSENTRY32);		//���ýṹ��ԱSize��С

	Process32First(SnapshotHandle, info);			//��ȡ��һ������
	while (Process32Next(SnapshotHandle, info) != false)		//����������һ����̼���ѭ��
	{
		/*		if (ColseProcessID == info->th32ProcessID)*/		//�ж��ǲ�����Ҫ�رյĽ���
		if (ProcessName == info->szExeFile)
		{
			ColseHandle = OpenProcess(PROCESS_TERMINATE, false, info->th32ProcessID);			//���Ѵ��ڽ��̷������о��
			TerminateProcess(ColseHandle, 0);													//�ս����
		}
		TRACE(_T("��ǰ���̣�%s\n"), info->szExeFile);
	}

	delete info;
}

void CrearThread(CDDDlg* dlg)
{

}

bool OpenGame(CString Path)
{
	CString Command = Path + " -fl";
	TRACE(_T("��Ϸ·����%s\n"), Path);
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
	EnumWindows(EnumChildWindowsProc, NULL); //ö�����д���
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
	if (GameTitle.Find("�������˲�") > -1) {
		TRACE("��ǰ��� %x :%s\n", hWnd, WindowTitle);
		g_GameHwnd.push_back(hWnd);
	}
	return true;
}



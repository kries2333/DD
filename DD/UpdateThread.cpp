#include "pch.h"
#include "UpdateThread.h"




#define BUF_SIZE_RES 1025


unsigned int __stdcall _UpdateThread(LPVOID p)
{
    CDDDlg* myDlg = (CDDDlg*)p;     //界面类为参数
	TLGAMEINFO* tGameInfo;			//游戏信息
	DWORD singleObjRet = 0;			//线程事件返回结果
	int UserIndex = 0;				//当前线程使用的数据下标

	CString szNameresult;			//共享内存名字作为标识
	CString Text;
	//获取当前线程句柄需要操作的数据
	for (int i = 0; i < myDlg->RunThread.size(); i++)
	{
		DWORD CurThread = GetCurrentThreadId();
		if (myDlg->RunThread.at(i).ThreadId == CurThread) {
			TRACE("获取当前线程所需的数据");
			UserIndex = i;
		}
	}

	szNameresult.Format("TL_Memory_%x",(DWORD)myDlg->RunThread.at(UserIndex).GameHwnd);
	TRACE("当前共享内存名字标识:%s\n", szNameresult);
	HANDLE hMapFileresult = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // 物理文件句柄
		NULL,                    // 默认安全级别
		PAGE_READWRITE,          // 可读可写
		0,                       // 高位文件大小
		BUF_SIZE_RES,            // 地位文件大小
		szNameresult             // 共享内存名称
	);

	LPVOID RESULT = (LPVOID)MapViewOfFile(
		hMapFileresult,      // 共享内存的句柄
		FILE_MAP_ALL_ACCESS, // 可读写许可
		NULL,
		NULL,
		BUF_SIZE_RES);
	if (RESULT != NULL) {
		tGameInfo = (TLGAMEINFO*)RESULT;
		//写入共享内存数据
		strcpy_s(tGameInfo->Account, myDlg->RunThread.at(UserIndex).UserName.GetBuffer());
		strcpy_s(tGameInfo->Password, myDlg->RunThread.at(UserIndex).Password.GetBuffer());
		strcpy_s(tGameInfo->Server, myDlg->RunThread.at(UserIndex).Server.GetBuffer());
		strcpy_s(tGameInfo->LuaScript, myDlg->RunThread.at(UserIndex).LuaScript.GetBuffer());
		tGameInfo->RoleIndex = _ttoi(myDlg->RunThread.at(UserIndex).RoleIndex);
		myDlg->RunThread.at(UserIndex).GameInfoMem = tGameInfo;
	}
	else {//申请共享内存失败
		return 0;
	}


	while (true)		//更新账号信息循环
	{
		singleObjRet = WaitForSingleObject(myDlg->RunThread.at(UserIndex).ExitEvent, 500);
		switch (singleObjRet)
		{
		case WAIT_TIMEOUT:
			TRACE("更新线程运行中: %x 窗口: %x\n", myDlg->RunThread.at(UserIndex).ThreadHandle, myDlg->RunThread.at(UserIndex).GameHwnd);
			for (int i = 0; i < myDlg->m_Page1.m_AccountList.GetItemCount(); i++)
			{
				//TRACE("共享内存地址%x\n", tGameInfo);
				if (myDlg->m_Page1.m_AccountList.GetItemText(i, 1) == myDlg->RunThread.at(UserIndex).UserName) {
					Text.Format("%d", myDlg->RunThread.at(UserIndex).GameHwnd);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 5, Text);		//更新窗口句柄
					Text.Format("%s", tGameInfo->RoleName);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 6, Text);		//更新名字
					Text.Format("%d", tGameInfo->RoleLv);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 7, Text);		//更新等级
					Text.Format("%s", tGameInfo->RoleSects);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 8, Text);		//更新门派
					Text.Format("%d", tGameInfo->RoleHp);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 10, Text);		//更新血量
					Text.Format("%s", tGameInfo->RoleState);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 12, Text);		//更新状态
				}
			}

			break;
		default:
			TRACE("线程结束,退出线程: %x\n", myDlg->RunThread.at(UserIndex).ThreadHandle);
			for (int i = 0; i < myDlg->m_Page1.m_AccountList.GetItemCount(); i++)
			{
				if (myDlg->m_Page1.m_AccountList.GetItemText(i, 1) == myDlg->RunThread.at(UserIndex).UserName) {
					Text.Format("%d", myDlg->RunThread.at(UserIndex).GameHwnd);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 5, "");

				}
			}
			UnmapViewOfFile(RESULT);
			CloseHandle(hMapFileresult);
			return 0;
		}
		//for (int i = 0; i < myDlg->m_Page1.m_AccountList.GetItemCount(); i++) {


		//}
		Sleep(500);
	}

    return 0;
}

unsigned int __stdcall _UpdateControlThread(LPVOID p)
{
	CDDDlg* myDlg = (CDDDlg*)p;     //界面类为参数
	SocketRunInfo runInfo;
	DWORD singleObjRet = 0;			//线程事件返回结果

	while (true)		//更新账号信息循环
	{
		TRACE("中控更新线程运行中:\n");
		singleObjRet = WaitForSingleObject(myDlg->m_UpdataControlThreadEvent, 500);
		switch (singleObjRet)
		{
		case WAIT_TIMEOUT:
			if (!myDlg->m_Page1.m_MyClientSoket.MyIsConnected()) {
				myDlg->m_Page1.m_MyClientSoket.MyStart();
				PrintInfo(myDlg, "正在连接中控");
				Sleep(5000);
				continue;
			}
			else {
				PrintInfo(myDlg, "中控已连接");
			}

			//发送list信息给中控
			for (int i = 0; i < myDlg->m_Page1.m_AccountList.GetItemCount(); i++)
			{
				ZeroMemory(&runInfo, sizeof(runInfo));
				strcpy(runInfo.tGameName, myDlg->m_Page1.m_AccountList.GetItemText(i, 1).GetBuffer());						//复制账号
				strcpy(runInfo.tGamePWD, myDlg->m_Page1.m_AccountList.GetItemText(i, 2).GetBuffer());						//复制密码
				strcpy(runInfo.tGameServerName, myDlg->m_Page1.m_AccountList.GetItemText(i, 4).GetBuffer());				//复制服务器
				strcpy(runInfo.tRoleName, myDlg->m_Page1.m_AccountList.GetItemText(i, 6).GetBuffer());						//复制角色名
				strcpy(runInfo.tMenPai, myDlg->m_Page1.m_AccountList.GetItemText(i, 8).GetBuffer());						//复制门派
				strcpy(runInfo.tState, myDlg->m_Page1.m_AccountList.GetItemText(i, 12).GetBuffer());						//复制状态
				strcpy(runInfo.tGameWnd, myDlg->m_Page1.m_AccountList.GetItemText(i, 5).GetBuffer());						//窗口名
				runInfo.tRoleLv = _ttoi(myDlg->m_Page1.m_AccountList.GetItemText(i, 7));									//当前角色等级
				runInfo.tIndex = i;																							//当前窗口下标
				myDlg->m_Page1.m_MyClientSoket.MySendPackets(SOCKET_GAME_INFO, sizeof(SocketRunInfo), (char*)&runInfo);		//发送消息
			}
			break;
		default:
			TRACE("中控更新线程结束,退出线程: %x");
			myDlg->m_Page1.m_MyClientSoket.MyStop();
			return 0;
		}

		Sleep(2000);
	}
}

void PrintInfo(CDDDlg* dlg, CString Info)
{
	CString Text = "运行状态:";
	Text += Info;
	::SendMessage(dlg->m_hWnd, WM_UpDataStatusBar, (WPARAM)3, (LPARAM)&Text);
}

void GetRunInfo(CDDDlg* myDlg, SocketRunInfo* runInfo)
{

}

#include "pch.h"
#include "UpdateThread.h"




#define BUF_SIZE_RES 1025


unsigned int __stdcall _UpdateThread(LPVOID p)
{
    CDDDlg* myDlg = (CDDDlg*)p;     //������Ϊ����
	TLGAMEINFO* tGameInfo;			//��Ϸ��Ϣ
	DWORD singleObjRet = 0;			//�߳��¼����ؽ��
	int UserIndex = 0;				//��ǰ�߳�ʹ�õ������±�

	CString szNameresult;			//�����ڴ�������Ϊ��ʶ
	CString Text;
	//��ȡ��ǰ�߳̾����Ҫ����������
	for (int i = 0; i < myDlg->RunThread.size(); i++)
	{
		DWORD CurThread = GetCurrentThreadId();
		if (myDlg->RunThread.at(i).ThreadId == CurThread) {
			TRACE("��ȡ��ǰ�߳����������");
			UserIndex = i;
		}
	}

	szNameresult.Format("TL_Memory_%x",(DWORD)myDlg->RunThread.at(UserIndex).GameHwnd);
	TRACE("��ǰ�����ڴ����ֱ�ʶ:%s\n", szNameresult);
	HANDLE hMapFileresult = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // �����ļ����
		NULL,                    // Ĭ�ϰ�ȫ����
		PAGE_READWRITE,          // �ɶ���д
		0,                       // ��λ�ļ���С
		BUF_SIZE_RES,            // ��λ�ļ���С
		szNameresult             // �����ڴ�����
	);

	LPVOID RESULT = (LPVOID)MapViewOfFile(
		hMapFileresult,      // �����ڴ�ľ��
		FILE_MAP_ALL_ACCESS, // �ɶ�д���
		NULL,
		NULL,
		BUF_SIZE_RES);
	if (RESULT != NULL) {
		tGameInfo = (TLGAMEINFO*)RESULT;
		//д�빲���ڴ�����
		strcpy_s(tGameInfo->Account, myDlg->RunThread.at(UserIndex).UserName.GetBuffer());
		strcpy_s(tGameInfo->Password, myDlg->RunThread.at(UserIndex).Password.GetBuffer());
		strcpy_s(tGameInfo->Server, myDlg->RunThread.at(UserIndex).Server.GetBuffer());
		strcpy_s(tGameInfo->LuaScript, myDlg->RunThread.at(UserIndex).LuaScript.GetBuffer());
		tGameInfo->RoleIndex = _ttoi(myDlg->RunThread.at(UserIndex).RoleIndex);
		myDlg->RunThread.at(UserIndex).GameInfoMem = tGameInfo;
	}
	else {//���빲���ڴ�ʧ��
		return 0;
	}


	while (true)		//�����˺���Ϣѭ��
	{
		singleObjRet = WaitForSingleObject(myDlg->RunThread.at(UserIndex).ExitEvent, 500);
		switch (singleObjRet)
		{
		case WAIT_TIMEOUT:
			TRACE("�����߳�������: %x ����: %x\n", myDlg->RunThread.at(UserIndex).ThreadHandle, myDlg->RunThread.at(UserIndex).GameHwnd);
			for (int i = 0; i < myDlg->m_Page1.m_AccountList.GetItemCount(); i++)
			{
				//TRACE("�����ڴ��ַ%x\n", tGameInfo);
				if (myDlg->m_Page1.m_AccountList.GetItemText(i, 1) == myDlg->RunThread.at(UserIndex).UserName) {
					Text.Format("%d", myDlg->RunThread.at(UserIndex).GameHwnd);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 5, Text);		//���´��ھ��
					Text.Format("%s", tGameInfo->RoleName);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 6, Text);		//��������
					Text.Format("%d", tGameInfo->RoleLv);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 7, Text);		//���µȼ�
					Text.Format("%s", tGameInfo->RoleSects);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 8, Text);		//��������
					Text.Format("%d", tGameInfo->RoleHp);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 10, Text);		//����Ѫ��
					Text.Format("%s", tGameInfo->RoleState);
					myDlg->m_Page1.m_AccountList.SetItemText(i, 12, Text);		//����״̬
				}
			}

			break;
		default:
			TRACE("�߳̽���,�˳��߳�: %x\n", myDlg->RunThread.at(UserIndex).ThreadHandle);
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
	CDDDlg* myDlg = (CDDDlg*)p;     //������Ϊ����
	SocketRunInfo runInfo;
	DWORD singleObjRet = 0;			//�߳��¼����ؽ��

	while (true)		//�����˺���Ϣѭ��
	{
		TRACE("�пظ����߳�������:\n");
		singleObjRet = WaitForSingleObject(myDlg->m_UpdataControlThreadEvent, 500);
		switch (singleObjRet)
		{
		case WAIT_TIMEOUT:
			if (!myDlg->m_Page1.m_MyClientSoket.MyIsConnected()) {
				myDlg->m_Page1.m_MyClientSoket.MyStart();
				PrintInfo(myDlg, "���������п�");
				Sleep(5000);
				continue;
			}
			else {
				PrintInfo(myDlg, "�п�������");
			}

			//����list��Ϣ���п�
			for (int i = 0; i < myDlg->m_Page1.m_AccountList.GetItemCount(); i++)
			{
				ZeroMemory(&runInfo, sizeof(runInfo));
				strcpy(runInfo.tGameName, myDlg->m_Page1.m_AccountList.GetItemText(i, 1).GetBuffer());						//�����˺�
				strcpy(runInfo.tGamePWD, myDlg->m_Page1.m_AccountList.GetItemText(i, 2).GetBuffer());						//��������
				strcpy(runInfo.tGameServerName, myDlg->m_Page1.m_AccountList.GetItemText(i, 4).GetBuffer());				//���Ʒ�����
				strcpy(runInfo.tRoleName, myDlg->m_Page1.m_AccountList.GetItemText(i, 6).GetBuffer());						//���ƽ�ɫ��
				strcpy(runInfo.tMenPai, myDlg->m_Page1.m_AccountList.GetItemText(i, 8).GetBuffer());						//��������
				strcpy(runInfo.tState, myDlg->m_Page1.m_AccountList.GetItemText(i, 12).GetBuffer());						//����״̬
				strcpy(runInfo.tGameWnd, myDlg->m_Page1.m_AccountList.GetItemText(i, 5).GetBuffer());						//������
				runInfo.tRoleLv = _ttoi(myDlg->m_Page1.m_AccountList.GetItemText(i, 7));									//��ǰ��ɫ�ȼ�
				runInfo.tIndex = i;																							//��ǰ�����±�
				myDlg->m_Page1.m_MyClientSoket.MySendPackets(SOCKET_GAME_INFO, sizeof(SocketRunInfo), (char*)&runInfo);		//������Ϣ
			}
			break;
		default:
			TRACE("�пظ����߳̽���,�˳��߳�: %x");
			myDlg->m_Page1.m_MyClientSoket.MyStop();
			return 0;
		}

		Sleep(2000);
	}
}

void PrintInfo(CDDDlg* dlg, CString Info)
{
	CString Text = "����״̬:";
	Text += Info;
	::SendMessage(dlg->m_hWnd, WM_UpDataStatusBar, (WPARAM)3, (LPARAM)&Text);
}

void GetRunInfo(CDDDlg* myDlg, SocketRunInfo* runInfo)
{

}

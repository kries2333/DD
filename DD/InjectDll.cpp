#include "pch.h"
#include "InjectDll.h"

#include <TlHelp32.h>

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ܣ�ע��dll
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
BOOL InJectDll(DWORD ProcessId, CString DllName)
{
	if (ProcessId == -1)
	{
		return FALSE;
	}

	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);

	if (!hProcess)
	{
		return FALSE;
	}

	//Ŀ�����������һƬ�ڴ�
	LPVOID lpBaseAddress = ::VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	if (!lpBaseAddress)
	{
		::CloseHandle(hProcess);
		return FALSE;
	}

	CString _CStrPath = GetCurPath(TRUE);
	if (_CStrPath.IsEmpty())
		return FALSE;

	_CStrPath += DllName;
	//DLL·��д��Ŀ�����
	BOOL bWrite = ::WriteProcessMemory(hProcess, lpBaseAddress, _CStrPath, MAX_PATH, NULL);
	if (!bWrite)
	{
		::CloseHandle(hProcess);
		return FALSE;
	}

	//����Զ���߳�ִ�м���DLL�ĺ���
	HANDLE hThread = ::CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, lpBaseAddress, 0, NULL);

	if (!hThread)
	{
		::CloseHandle(hProcess);
		return FALSE;
	}


	::WaitForSingleObject(hThread, INFINITE);

	//������Ŀ��������������һƬ�ڴ�
	::VirtualFreeEx(hProcess, lpBaseAddress, 4096, MEM_DECOMMIT);
	CloseHandle(hProcess);
	return TRUE;
}

/************************************************************************
ж��DLL
************************************************************************/
BOOL UnInJectDll(DWORD ProcessId, CString DllName)
{
	if (ProcessId == -1)
	{
		return FALSE;
	}

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessId);

	MODULEENTRY32 me32;
	me32.dwSize = sizeof(me32);

	//����ƥ��Ľ�������
	BOOL bRet = Module32First(hSnap, &me32);
	while (bRet)
	{
		if (lstrcmp(me32.szExePath, DllName) == 0)
		{
			break;
		}
		bRet = Module32Next(hSnap, &me32);
	}

	CloseHandle(hSnap);

	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);

	if (!hProcess)
	{
		return FALSE;
	}

	//����Զ���߳�ִ��xж��DLL�ĺ���
	HANDLE hThread = ::CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, me32.hModule, 0, NULL);

	if (!hThread)
	{
		::CloseHandle(hProcess);
		return FALSE;
	}

	::WaitForSingleObject(hThread, INFINITE);

	//������Ŀ��������������һƬ�ڴ�

	CloseHandle(hThread);
	CloseHandle(hProcess);
	return TRUE;
}


/************************************************************************
��ȡ·��
************************************************************************/
CString GetCurPath(BOOL slash)
{

	TCHAR lpBuffer[MAX_PATH] = { 0 };
	if (GetModuleFileName(
		NULL,
		lpBuffer,
		MAX_PATH
	) == NULL)
	{
		return CString();
	}

	CString CStrPath(lpBuffer);
	int npos = CStrPath.ReverseFind(_T('\\'));//�������
	if (npos != -1)
	{
		if (slash == TRUE)
			CStrPath = CStrPath.Mid(0, npos + 1);//��ȡ��0��ʼ���ַ�������б��
		else
			CStrPath = CStrPath.Mid(0, npos);//��ȡ��0��ʼ���ַ�����Ҫб��
		//dbgPrint(_T("%s::\t\t %s\n"), CString(__FUNCTION__), CStrPath);
	}

	return CStrPath;
}
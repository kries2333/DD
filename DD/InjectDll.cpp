#include "pch.h"
#include "InjectDll.h"

#include <TlHelp32.h>

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//功能：注入dll
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

	//目标程序中申请一片内存
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
	//DLL路径写到目标进程
	BOOL bWrite = ::WriteProcessMemory(hProcess, lpBaseAddress, _CStrPath, MAX_PATH, NULL);
	if (!bWrite)
	{
		::CloseHandle(hProcess);
		return FALSE;
	}

	//开启远程线程执行加载DLL的函数
	HANDLE hThread = ::CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, lpBaseAddress, 0, NULL);

	if (!hThread)
	{
		::CloseHandle(hProcess);
		return FALSE;
	}


	::WaitForSingleObject(hThread, INFINITE);

	//清理在目标程序中申请的那一片内存
	::VirtualFreeEx(hProcess, lpBaseAddress, 4096, MEM_DECOMMIT);
	CloseHandle(hProcess);
	return TRUE;
}

/************************************************************************
卸载DLL
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

	//查找匹配的进程名称
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

	//开启远程线程执行x卸载DLL的函数
	HANDLE hThread = ::CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, me32.hModule, 0, NULL);

	if (!hThread)
	{
		::CloseHandle(hProcess);
		return FALSE;
	}

	::WaitForSingleObject(hThread, INFINITE);

	//清理在目标程序中申请的那一片内存

	CloseHandle(hThread);
	CloseHandle(hProcess);
	return TRUE;
}


/************************************************************************
获取路径
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
	int npos = CStrPath.ReverseFind(_T('\\'));//逆向查找
	if (npos != -1)
	{
		if (slash == TRUE)
			CStrPath = CStrPath.Mid(0, npos + 1);//截取从0开始的字符串保留斜杠
		else
			CStrPath = CStrPath.Mid(0, npos);//截取从0开始的字符串不要斜杠
		//dbgPrint(_T("%s::\t\t %s\n"), CString(__FUNCTION__), CStrPath);
	}

	return CStrPath;
}
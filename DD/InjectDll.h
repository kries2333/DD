#pragma once

CString GetCurPath(BOOL slash);

BOOL InJectDll(DWORD ProcessId, CString DllName);
BOOL UnInJectDll(DWORD ProcessId, CString DllName);
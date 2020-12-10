#pragma once
#include "SocketStruct.h"
#include "DDDlg.h"

unsigned int WINAPI _UpdateThread(LPVOID p);

unsigned int WINAPI _UpdateControlThread(LPVOID p);

void PrintInfo(CDDDlg* dlg, CString Info);

void GetRunInfo(CDDDlg* myDlg, SocketRunInfo* runInfo);
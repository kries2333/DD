#pragma once
#include "pch.h"
#include "DDDlg.h"

unsigned int WINAPI WorkThread(LPVOID p);

void WINAPI RunTime(CDDDlg* dlg, CString Info);

void WINAPI CloseMyWindow(CString ProcessName);

void CrearThread(CDDDlg* dlg);

bool OpenGame(CString Path);

bool GameIsRun(CDDDlg* dlg, int RunCount);

BOOL CALLBACK EnumChildWindowsProc(HWND hWnd, LPARAM lParam);

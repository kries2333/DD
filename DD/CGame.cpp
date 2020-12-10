#include "pch.h"
#include "CGame.h"

bool CGame::OpenGame(CString gamePath)
{
	TRACE("打开游戏");
	HWND		LoginWindow = 0;			//登录窗口
	bool		IsOpen = false;				//是否执行打开

	int retCode = 0;

	LoginWindow = FindWindow("TianLongBaBuHJ WndClass","《新天龙八部》");
	if (0 != LoginWindow) {
		TRACE(_T("游戏已打开"));
		return true;
	}

	if (!IsOpen) {
		CString line;
		line.Format("%s", gamePath + " -fl");
		TRACE(_T("执行命令：%s\n"), line);
		//system(line.GetBuffer());
		/*ShellExecute(m_dlg->m_hWnd, NULL, line, NULL, NULL, SW_HIDE);*/
		/*system("start " + line);*/
		int RunRet = WinExec(line, SW_SHOW);
		//if (ERROR_FILE_NOT_FOUND == RunRet) {
		//	m_dlg->MyPrintInfo.MessageBox("游戏路径错误");
		//	retCode = false;
		//	goto End;
		//}

		IsOpen = true;
	}
	return retCode;
}

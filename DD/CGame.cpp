#include "pch.h"
#include "CGame.h"

bool CGame::OpenGame(CString gamePath)
{
	TRACE("����Ϸ");
	HWND		LoginWindow = 0;			//��¼����
	bool		IsOpen = false;				//�Ƿ�ִ�д�

	int retCode = 0;

	LoginWindow = FindWindow("TianLongBaBuHJ WndClass","���������˲���");
	if (0 != LoginWindow) {
		TRACE(_T("��Ϸ�Ѵ�"));
		return true;
	}

	if (!IsOpen) {
		CString line;
		line.Format("%s", gamePath + " -fl");
		TRACE(_T("ִ�����%s\n"), line);
		//system(line.GetBuffer());
		/*ShellExecute(m_dlg->m_hWnd, NULL, line, NULL, NULL, SW_HIDE);*/
		/*system("start " + line);*/
		int RunRet = WinExec(line, SW_SHOW);
		//if (ERROR_FILE_NOT_FOUND == RunRet) {
		//	m_dlg->MyPrintInfo.MessageBox("��Ϸ·������");
		//	retCode = false;
		//	goto End;
		//}

		IsOpen = true;
	}
	return retCode;
}

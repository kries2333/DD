#pragma once
#include "MyClientSocket.h"
// dlg1 对话框

class dlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(dlg1)

public:
	dlg1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dlg1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	bool SplitCStringArr(CString expression, CString delimiter, CStringArray* resultArr);

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
	

public:
	CString m_GamePath;								//游戏路径
	HANDLE	m_WorkThreadEvent;						//工作线程事件

public:
	bool Start();									//启动线程
	bool Stop();									//停止所有线程
	void InitData();								//初始化功能

public:
	CListCtrl m_AccountList;
	MyClientSocket m_MyClientSoket;					//客户端socket对象
	HANDLE m_WorkThread;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	CEdit m_RunCount;
	afx_msg void OnBnClickedButton3();
	CEdit m_EditGamePath;
	afx_msg void OnBnClickedButton6();
	CEdit m_EditMachineName;
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnNMRClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void On32771();
	afx_msg void On032772();
	afx_msg void OnBnClickedButton2();
};

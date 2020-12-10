#pragma once

// CDlgReg 对话框

unsigned int WINAPI Login(LPVOID p);

class CDlgReg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgReg)

public:
	CDlgReg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgReg();



// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnClose();
	afx_msg LRESULT OnCloseMsg(WPARAM wparam, LPARAM lparam);

	void CloseRegWindow();
	void* m_ParentDlg = NULL;
};

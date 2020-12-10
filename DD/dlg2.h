#pragma once


// dlg2 对话框

class dlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(dlg2)

public:
	dlg2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dlg2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListTaskSelete;
	CListCtrl m_ListTaskRun;
	afx_msg void OnNMDblclkList4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclkList5(NMHDR* pNMHDR, LRESULT* pResult);
};

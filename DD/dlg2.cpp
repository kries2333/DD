// dlg2.cpp: 实现文件
//

#include "pch.h"
#include "DD.h"
#include "dlg2.h"
#include "afxdialogex.h"


// dlg2 对话框

IMPLEMENT_DYNAMIC(dlg2, CDialogEx)

dlg2::dlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

dlg2::~dlg2()
{
}

void dlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST4, m_ListTaskSelete);
	DDX_Control(pDX, IDC_LIST5, m_ListTaskRun);
}


BEGIN_MESSAGE_MAP(dlg2, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST4, &dlg2::OnNMDblclkList4)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST5, &dlg2::OnNMDblclkList5)
END_MESSAGE_MAP()

// dlg2 消息处理程序
void dlg2::OnNMDblclkList4(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	TRACE("写入执行任务\n");

	CString Text;
	int Cur;
	Cur = m_ListTaskSelete.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	Text = m_ListTaskSelete.GetItemText(Cur, 0);
	TRACE("添加任务：%s\n", Text);

	int n = m_ListTaskRun.GetItemCount();
	m_ListTaskRun.InsertItem(n, Text);

}


void dlg2::OnNMDblclkList5(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	TRACE("删除执行任务\n");

	CString Text;
	int Cur;
	Cur = m_ListTaskRun.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	Text = m_ListTaskRun.GetItemText(Cur, 0);
	TRACE("删除任务：%s\n", Text);

	m_ListTaskRun.DeleteItem(Cur);
}



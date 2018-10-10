#pragma once
#include "afxcmn.h"


// RelocationDlg 对话框

class RelocationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RelocationDlg)

public:
	RelocationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RelocationDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = Relocation };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_FirstReloc;
	CListCtrl m_SecondReloc;
	void ShowRelocation();//显示重定位
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};

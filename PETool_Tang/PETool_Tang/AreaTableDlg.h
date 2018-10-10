#pragma once
#include "afxcmn.h"


// AreaTableDlg 对话框

class AreaTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AreaTableDlg)

public:
	AreaTableDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AreaTableDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = AreaTable };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_AreaTabList;
	void ShowAreaTable();//显示区段表
	virtual BOOL OnInitDialog();
};

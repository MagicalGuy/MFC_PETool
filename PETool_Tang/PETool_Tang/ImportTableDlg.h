#pragma once
#include "afxcmn.h"


// ImportTableDlg 对话框

class ImportTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ImportTableDlg)

public:
	ImportTableDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ImportTableDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = ImportTable };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ShowImportList();		//显示输入表信息
	CListCtrl m_UpImport;
	CListCtrl m_DownImport;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};

#pragma once
#include "afxcmn.h"


// ExportTableDlg 对话框

class ExportTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ExportTableDlg)

public:
	ExportTableDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ExportTableDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = ExportTable };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	void ShowExportInfo();		//显示输出表信息	
	void ShowExportList();		//显示输出表信息

	CString m_ExportOffest;//输出表偏移
	CString m_Characteristic;//特征值
	CString m_Plot;//基址
	CString m_Name;//名称
	CString m_NameString;//名称字串
	CString m_FunctionNumber;//函数数量
	CString m_FunctionNameNumber;//函数名数量
	CString m_FunctionAddr;//函数地址
	CString m_FunctionNameAddr;//函数名称地址
	CString m_FunSerialNumberAddr;//序号表地址
	CListCtrl m_ExportList;
	virtual BOOL OnInitDialog();
};

#pragma once
#include "afxcmn.h"
#include"CMyList.h"


// DelayTableDlg 对话框

class DelayTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DelayTableDlg)

public:
	DelayTableDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DelayTableDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DelayTable };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyList m_ListDelayDll;
	CMyList m_ListDelayFun;

	CString m_DelayDllName;					//DLL名
	CString m_DelayNameRVA;					//RVA
	CString m_DelayINT;						//INT
	CString m_DelayIAT;						//IAT

	CString m_DelayFunOrdinal;				//函数序号
	CString m_DelayFunName;					//函数名称

	PIMAGE_THUNK_DATA32  m_pDelayThunk;		//INT表

	void GetDelayDllInfo();					//获取DLL信息
	void GetDelayFunInfo();					//获取函数信息
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();

	DWORD RVA2FO(DWORD dwRva);
};

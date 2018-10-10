#pragma once
#include "afxcmn.h"
#include"CMyList.h"


// DelayTableDlg �Ի���

class DelayTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DelayTableDlg)

public:
	DelayTableDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DelayTableDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = DelayTable };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMyList m_ListDelayDll;
	CMyList m_ListDelayFun;

	CString m_DelayDllName;					//DLL��
	CString m_DelayNameRVA;					//RVA
	CString m_DelayINT;						//INT
	CString m_DelayIAT;						//IAT

	CString m_DelayFunOrdinal;				//�������
	CString m_DelayFunName;					//��������

	PIMAGE_THUNK_DATA32  m_pDelayThunk;		//INT��

	void GetDelayDllInfo();					//��ȡDLL��Ϣ
	void GetDelayFunInfo();					//��ȡ������Ϣ
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();

	DWORD RVA2FO(DWORD dwRva);
};

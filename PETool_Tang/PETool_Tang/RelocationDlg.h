#pragma once
#include "afxcmn.h"


// RelocationDlg �Ի���

class RelocationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RelocationDlg)

public:
	RelocationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RelocationDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = Relocation };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_FirstReloc;
	CListCtrl m_SecondReloc;
	void ShowRelocation();//��ʾ�ض�λ
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};

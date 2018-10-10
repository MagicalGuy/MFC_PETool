#pragma once
#include "afxcmn.h"


// ImportTableDlg �Ի���

class ImportTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ImportTableDlg)

public:
	ImportTableDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ImportTableDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = ImportTable };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void ShowImportList();		//��ʾ�������Ϣ
	CListCtrl m_UpImport;
	CListCtrl m_DownImport;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};

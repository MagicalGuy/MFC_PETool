#pragma once
#include "afxcmn.h"


// AreaTableDlg �Ի���

class AreaTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AreaTableDlg)

public:
	AreaTableDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AreaTableDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = AreaTable };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_AreaTabList;
	void ShowAreaTable();//��ʾ���α�
	virtual BOOL OnInitDialog();
};

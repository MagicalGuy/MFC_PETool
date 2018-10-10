#pragma once
#include "afxcmn.h"


// ExportTableDlg �Ի���

class ExportTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ExportTableDlg)

public:
	ExportTableDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ExportTableDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = ExportTable };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	void ShowExportInfo();		//��ʾ�������Ϣ	
	void ShowExportList();		//��ʾ�������Ϣ

	CString m_ExportOffest;//�����ƫ��
	CString m_Characteristic;//����ֵ
	CString m_Plot;//��ַ
	CString m_Name;//����
	CString m_NameString;//�����ִ�
	CString m_FunctionNumber;//��������
	CString m_FunctionNameNumber;//����������
	CString m_FunctionAddr;//������ַ
	CString m_FunctionNameAddr;//�������Ƶ�ַ
	CString m_FunSerialNumberAddr;//��ű��ַ
	CListCtrl m_ExportList;
	virtual BOOL OnInitDialog();
};

#pragma once


// CatalogDlg �Ի���

class CatalogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CatalogDlg)

public:
	CatalogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CatalogDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = Catalog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	void ShowPeInfo();
	void OutPutPeInfo(CString &m_PeRvaInfo, CString &m_PeSizeInfo, DWORD PeRvaValue, DWORD PeSizeValue);//���PE�����Ϣ

	CString m_ExportRva;//�����
	CString m_ExportSize;
	CString m_ImportRva;//�����
	CString m_ImportSize;
	CString m_ResourceRva;//��Դ��
	CString m_ResourceSize;
	CString m_ExceptionRva;//����
	CString m_ExceptionSize;
	CString m_SecurityRva;//��ȫ
	CString m_SecuritySize;
	CString m_BaserelocRva;//�ض�λ
	CString m_BaserelocSize;
	CString M_DebugRva;//����
	CString M_DebugSize;
	CString m_ArchitectureRva;//��Ȩ
	CString m_ArchitectureSize;
	CString m_GlobalptrRva;//ȫ��ָ��
	CString m_GlobalptrSize;
	CString m_TlsRva;//TLS
	CString m_TlsSize;
	CString m_LoadConfigRva;//��������
	CString m_LoadConfigSize;
	CString m_BoundImportRva;//���뷶Χ
	CString m_BoundImportSize;
	CString m_IatRva;//IAT
	CString m_IatSize;
	CString m_DelayImportRva;//�ӳټ��ر�
	CString m_DelayImportSize;
	CString m_ComDescriptorRva;//com
	CString m_ComDescriptorSize;
	afx_msg void OnBnClickedButton17();//�����
	afx_msg void OnBnClickedButton18();//�����
	afx_msg void OnBnClickedButton19();//��Դ��
	afx_msg void OnBnClickedButton20();//�ض�λ
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton21();//�ֲ��̴߳洢
	afx_msg void OnBnClickedButton22();//�ӳټ��ر�
};

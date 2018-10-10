#pragma once


// FileLocationDlg �Ի���

class FileLocationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FileLocationDlg)

public:
	FileLocationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FileLocationDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = FileLocation };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void  LockEdit(int EditId);					//����ָ���༭��

	afx_msg void OnBnClickedButton1();//ѡ��VA
	afx_msg void OnBnClickedButton2();//ѡ��rva
	afx_msg void OnBnClickedButton3();//ѡ��FOA
	afx_msg void OnEnChangeEdit1();//�ı��ı���
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	CString m_Va;
	CString m_Rva;
	CString m_Offset;
	CString m_Section;//����
	CString m_Byte;//�ֽ�

	CString m_StrPDosAddr;


	DWORD ExclusiveCalcOffset(DWORD Rva);

	DWORD FoaToRva(DWORD dwFoa);//�ļ���ַת�����ڴ��ַ

	afx_msg void OnBnClickedButton4();//����
};

#pragma once
#include "CMyList.h"


// CPETLS �Ի���

class TLSTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TLSTableDlg)

public:
	TLSTableDlg(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TLSTableDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = TLSTable };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	PIMAGE_DOS_HEADER m_pDos;		   //DOSͷ
	PIMAGE_NT_HEADERS32 m_pNTHeader;   //NTͷ
	PIMAGE_DATA_DIRECTORY m_pDataDir;  //Ŀ¼ͷ
	CString m_FunAdd;				   //������ַ

	CMyList m_ListTLS;				   //TLS�б�

	CString m_StartAddressOfRawData;//��ʼ��ַ
	CString m_EndAddressOfRawData;//������ַ
	CString m_AddressOfIndex;//����
	CString m_AddressOfCallBacks;//�ص�����
	CString m_SizeOfZeroFill;//���0����
	CString m_Characteristics;//����


	void GetTLSInfo();				   //��ȡTLS��Ϣ
	DWORD RVA2FO(DWORD dwRva, PIMAGE_NT_HEADERS32 pNt);//rvaתfoa
};

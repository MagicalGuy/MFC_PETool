// TLSTableDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool_Tang.h"
#include "TLSTableDlg.h"
#include "afxdialogex.h"


// TLSTableDlg �Ի���

IMPLEMENT_DYNAMIC(TLSTableDlg, CDialogEx)

TLSTableDlg::TLSTableDlg(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent /*=NULL*/)
	: CDialogEx(TLSTable, pParent)
	, m_StartAddressOfRawData(_T(""))
	, m_EndAddressOfRawData(_T(""))
	, m_AddressOfIndex(_T(""))
	, m_AddressOfCallBacks(_T(""))
	, m_SizeOfZeroFill(_T(""))
	, m_Characteristics(_T(""))
{
	m_pDos = pDos;
	m_pNTHeader = pNTHeader;
	m_pDataDir = pNTHeader->OptionalHeader.DataDirectory;
}

TLSTableDlg::~TLSTableDlg()
{
}

void TLSTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_StartAddressOfRawData);
	DDX_Text(pDX, IDC_EDIT2, m_EndAddressOfRawData);
	DDX_Text(pDX, IDC_EDIT3, m_AddressOfIndex);
	DDX_Text(pDX, IDC_EDIT4, m_AddressOfCallBacks);
	DDX_Text(pDX, IDC_EDIT5, m_SizeOfZeroFill);
	DDX_Text(pDX, IDC_EDIT6, m_Characteristics);
	DDX_Control(pDX, IDC_LIST1, m_ListTLS);
}


BEGIN_MESSAGE_MAP(TLSTableDlg, CDialogEx)
END_MESSAGE_MAP()


// CPETLS ��Ϣ�������


BOOL TLSTableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListTLS.AddColumn(2, L"����", 100, L"������ַ", 300);
	GetTLSInfo();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

//****************************************************************
// Brief 	: ��ȡTLS��Ϣ
// Method	: GetTLSInfo
// FullName	: CPETLS::GetTLSInfo
// Access	: private 
// Returns	: void
//****************************************************************

void TLSTableDlg::GetTLSInfo()
{
	PBYTE pBuf = (PBYTE)m_pDos;
	PIMAGE_TLS_DIRECTORY32 pTLS = (PIMAGE_TLS_DIRECTORY32)(pBuf +
		RVA2FO(m_pDataDir[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress, m_pNTHeader));

	m_StartAddressOfRawData.Format(L"%p", pTLS->StartAddressOfRawData);
	m_EndAddressOfRawData.Format(L"%p", pTLS->EndAddressOfRawData);
	m_AddressOfIndex.Format(L"%08X", pTLS->AddressOfIndex);
	m_AddressOfCallBacks.Format(L"%p", pTLS->AddressOfCallBacks);
	m_SizeOfZeroFill.Format(L"%08X", pTLS->SizeOfZeroFill);
	m_Characteristics.Format(L"%08X", pTLS->Characteristics);

	DWORD dwRVA;
	//�ҵ��ص�����-
	if (AnalPE.pOptH !=NULL) {
	//DWORD dwRVA = pTLS->AddressOfCallBacks - m_pNTHeader->OptionalHeader.ImageBase;
	 dwRVA = pTLS->AddressOfCallBacks - AnalPE.pOptH->ImageBase;
	}
	if (AnalPE.pOptH64 != NULL) {
		dwRVA = pTLS->AddressOfCallBacks - AnalPE.pOptH64->ImageBase;
	}

	PWORD pFunAdd = (PWORD)(pBuf + RVA2FO(dwRVA, m_pNTHeader));

	DWORD dwIndex = 0;
	CString strIndex;
	while (*pFunAdd)
	{
		strIndex.Format(L"%d", dwIndex);
		m_FunAdd.Format(L"%p", *pFunAdd);
		m_ListTLS.AddItem(2, strIndex, m_FunAdd);
		pFunAdd++;
		dwIndex++; 
	}

}

DWORD TLSTableDlg::RVA2FO(DWORD dwRva, PIMAGE_NT_HEADERS32 pNt)
{
	//�ļ��������ڴ�������
	if (pNt->OptionalHeader.FileAlignment == pNt->OptionalHeader.SectionAlignment)
	{
		return dwRva;
	}
	//����ͷ
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(pNt);

	//ѭ������
	for (int i = 0; i < pNt->FileHeader.NumberOfSections; i++)
	{
		//�ȶԵ�ַ
		if (dwRva >= pSec[i].VirtualAddress&&
			dwRva <= pSec[i].VirtualAddress + pSec[i].SizeOfRawData)
		{
			return	dwRva - pSec[i].VirtualAddress + pSec[i].PointerToRawData;
		}
	}

	return -1;

}

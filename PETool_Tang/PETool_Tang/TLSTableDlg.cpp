// TLSTableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool_Tang.h"
#include "TLSTableDlg.h"
#include "afxdialogex.h"


// TLSTableDlg 对话框

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


// CPETLS 消息处理程序


BOOL TLSTableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListTLS.AddColumn(2, L"索引", 100, L"函数地址", 300);
	GetTLSInfo();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//****************************************************************
// Brief 	: 获取TLS信息
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
	//找到回调函数-
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
	//文件对齐与内存对齐相等
	if (pNt->OptionalHeader.FileAlignment == pNt->OptionalHeader.SectionAlignment)
	{
		return dwRva;
	}
	//区段头
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(pNt);

	//循环查找
	for (int i = 0; i < pNt->FileHeader.NumberOfSections; i++)
	{
		//比对地址
		if (dwRva >= pSec[i].VirtualAddress&&
			dwRva <= pSec[i].VirtualAddress + pSec[i].SizeOfRawData)
		{
			return	dwRva - pSec[i].VirtualAddress + pSec[i].PointerToRawData;
		}
	}

	return -1;

}

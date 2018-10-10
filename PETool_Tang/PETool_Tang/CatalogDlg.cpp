// CatalogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool_Tang.h"
#include "CatalogDlg.h"
#include "afxdialogex.h"
#include "ExportTableDlg.h"
#include"ImportTableDlg.h"
#include"ResourceDlg.h"
#include "RelocationDlg.h"
#include"TLSTableDlg.h"
#include"DelayTableDlg.h"


// CatalogDlg 对话框

IMPLEMENT_DYNAMIC(CatalogDlg, CDialogEx)

CatalogDlg::CatalogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Catalog, pParent)
	, m_ExportRva(_T(""))
	, m_ExportSize(_T(""))
	, m_ImportRva(_T(""))
	, m_ImportSize(_T(""))
	, m_ResourceRva(_T(""))
	, m_ResourceSize(_T(""))
	, m_ExceptionRva(_T(""))
	, m_ExceptionSize(_T(""))
	, m_SecurityRva(_T(""))
	, m_SecuritySize(_T(""))
	, m_BaserelocRva(_T(""))
	, m_BaserelocSize(_T(""))
	, M_DebugRva(_T(""))
	, M_DebugSize(_T(""))
	, m_ArchitectureRva(_T(""))
	, m_ArchitectureSize(_T(""))
	, m_GlobalptrRva(_T(""))
	, m_GlobalptrSize(_T(""))
	, m_TlsRva(_T(""))
	, m_TlsSize(_T(""))
	, m_LoadConfigRva(_T(""))
	, m_LoadConfigSize(_T(""))
	, m_BoundImportRva(_T(""))
	, m_BoundImportSize(_T(""))
	, m_IatRva(_T(""))
	, m_IatSize(_T(""))
	, m_DelayImportRva(_T(""))
	, m_DelayImportSize(_T(""))
	, m_ComDescriptorRva(_T(""))
	, m_ComDescriptorSize(_T(""))
{

}

CatalogDlg::~CatalogDlg()
{
}

void CatalogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ExportRva);
	DDX_Text(pDX, IDC_EDIT2, m_ExportSize);
	DDX_Text(pDX, IDC_EDIT13, m_ImportRva);
	DDX_Text(pDX, IDC_EDIT4, m_ImportSize);
	DDX_Text(pDX, IDC_EDIT14, m_ResourceRva);
	DDX_Text(pDX, IDC_EDIT6, m_ResourceSize);
	DDX_Text(pDX, IDC_EDIT15, m_ExceptionRva);
	DDX_Text(pDX, IDC_EDIT8, m_ExceptionSize);
	DDX_Text(pDX, IDC_EDIT5, m_SecurityRva);
	DDX_Text(pDX, IDC_EDIT10, m_SecuritySize);
	DDX_Text(pDX, IDC_EDIT7, m_BaserelocRva);
	DDX_Text(pDX, IDC_EDIT11, m_BaserelocSize);
	DDX_Text(pDX, IDC_EDIT9, M_DebugRva);
	DDX_Text(pDX, IDC_EDIT3, M_DebugSize);
	DDX_Text(pDX, IDC_EDIT12, m_ArchitectureRva);
	DDX_Text(pDX, IDC_EDIT21, m_ArchitectureSize);
	DDX_Text(pDX, IDC_EDIT18, m_GlobalptrRva);
	DDX_Text(pDX, IDC_EDIT22, m_GlobalptrSize);
	DDX_Text(pDX, IDC_EDIT16, m_TlsRva);
	DDX_Text(pDX, IDC_EDIT23, m_TlsSize);
	DDX_Text(pDX, IDC_EDIT17, m_LoadConfigRva);
	DDX_Text(pDX, IDC_EDIT24, m_LoadConfigSize);
	DDX_Text(pDX, IDC_EDIT19, m_BoundImportRva);
	DDX_Text(pDX, IDC_EDIT25, m_BoundImportSize);
	DDX_Text(pDX, IDC_EDIT20, m_IatRva);
	DDX_Text(pDX, IDC_EDIT27, m_IatSize);
	DDX_Text(pDX, IDC_EDIT26, m_DelayImportRva);
	DDX_Text(pDX, IDC_EDIT32, m_DelayImportSize);
	DDX_Text(pDX, IDC_EDIT28, m_ComDescriptorRva);
	DDX_Text(pDX, IDC_EDIT31, m_ComDescriptorSize);
}


void CatalogDlg::ShowPeInfo()
{
	if (AnalPE.pNtH == NULL)
	{
		return;
	}

	AnalPE.OutPutPeInfo(m_ExportRva, AnalPE.pDatD[0].VirtualAddress);
	AnalPE.OutPutPeInfo(m_ExportSize, AnalPE.pDatD[0].Size);
	AnalPE.OutPutPeInfo(m_ImportRva, AnalPE.pDatD[1].VirtualAddress);
	AnalPE.OutPutPeInfo(m_ImportSize, AnalPE.pDatD[1].Size);
	AnalPE.OutPutPeInfo(m_ResourceRva, AnalPE.pDatD[2].VirtualAddress);
	AnalPE.OutPutPeInfo(m_ResourceSize, AnalPE.pDatD[2].Size);
	AnalPE.OutPutPeInfo(m_ExceptionRva, AnalPE.pDatD[3].VirtualAddress);
	AnalPE.OutPutPeInfo(m_ExceptionSize, AnalPE.pDatD[3].Size);
	AnalPE.OutPutPeInfo(m_SecurityRva, AnalPE.pDatD[4].VirtualAddress);
	AnalPE.OutPutPeInfo(m_SecuritySize, AnalPE.pDatD[4].Size);
	AnalPE.OutPutPeInfo(m_BaserelocRva, AnalPE.pDatD[5].VirtualAddress);
	AnalPE.OutPutPeInfo(m_BaserelocSize, AnalPE.pDatD[5].Size);
	AnalPE.OutPutPeInfo(M_DebugRva, AnalPE.pDatD[6].VirtualAddress);
	AnalPE.OutPutPeInfo(M_DebugSize, AnalPE.pDatD[6].Size);
	AnalPE.OutPutPeInfo(m_ArchitectureRva, AnalPE.pDatD[7].VirtualAddress);
	AnalPE.OutPutPeInfo(m_ArchitectureSize, AnalPE.pDatD[7].Size);
	AnalPE.OutPutPeInfo(m_GlobalptrRva, AnalPE.pDatD[8].VirtualAddress);
	AnalPE.OutPutPeInfo(m_GlobalptrSize, AnalPE.pDatD[8].Size);
	AnalPE.OutPutPeInfo(m_TlsRva, AnalPE.pDatD[9].VirtualAddress);
	AnalPE.OutPutPeInfo(m_TlsSize, AnalPE.pDatD[9].Size);
	AnalPE.OutPutPeInfo(m_LoadConfigRva, AnalPE.pDatD[10].VirtualAddress);
	AnalPE.OutPutPeInfo(m_LoadConfigSize, AnalPE.pDatD[10].Size);
	AnalPE.OutPutPeInfo(m_BoundImportRva, AnalPE.pDatD[11].VirtualAddress);
	AnalPE.OutPutPeInfo(m_BoundImportSize, AnalPE.pDatD[11].Size);
	AnalPE.OutPutPeInfo(m_IatRva, AnalPE.pDatD[12].VirtualAddress);
	AnalPE.OutPutPeInfo(m_IatSize, AnalPE.pDatD[12].Size);
	AnalPE.OutPutPeInfo(m_DelayImportRva, AnalPE.pDatD[13].VirtualAddress);
	AnalPE.OutPutPeInfo(m_DelayImportSize, AnalPE.pDatD[13].Size);
	AnalPE.OutPutPeInfo(m_ComDescriptorRva, AnalPE.pDatD[14].VirtualAddress);
	AnalPE.OutPutPeInfo(m_ComDescriptorSize, AnalPE.pDatD[14].Size);
	UpdateData(FALSE);
}

void CatalogDlg::OutPutPeInfo(CString &m_PeRvaInfo, CString &m_PeSizeInfo, DWORD PeRvaValue, DWORD PeSizeValue)
{
	CString StrRvaValue, StrSizeValue;
	StrRvaValue.Format(L"%08X", PeRvaValue);//转16进制
	StrSizeValue.Format(L"%08X", PeSizeValue);//转16进制
	m_PeRvaInfo = StrRvaValue;
	m_PeSizeInfo = StrSizeValue;
	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CatalogDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON17, &CatalogDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CatalogDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CatalogDlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CatalogDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CatalogDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CatalogDlg::OnBnClickedButton22)
END_MESSAGE_MAP()


// CatalogDlg 消息处理程序


void CatalogDlg::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	if (AnalPE.buf == NULL)
	{
		AfxMessageBox(L"请拖入PE文件");
		return;
	}
	if (AnalPE.pDatD->Size == 0)
	{
		AfxMessageBox(L"无导出表");
		return;
	}
	ExportTableDlg dlg;
	dlg.DoModal();

}


void CatalogDlg::OnBnClickedButton18()
{
	// TODO: 在此添加控件通知处理程序代码
	if (AnalPE.buf == NULL)
	{
		AfxMessageBox(L"请拖入PE文件");
		return;
	}
	ImportTableDlg dlg;
	dlg.DoModal();

}


void CatalogDlg::OnBnClickedButton19()
{
	// TODO: 在此添加控件通知处理程序代码
	if (AnalPE.buf == NULL)
	{
		AfxMessageBox(L"请拖入PE文件");
		return;
	}
	ResourceDlg dlg;

	if (AnalPE.pOptH != NULL) {
		dlg.m_dwResRootRva = AnalPE.pOptH->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress;
		dlg.m_pResRoot = (IMAGE_RESOURCE_DIRECTORY*)(dlg.m_dwResRootRva + (DWORD)AnalPE.pDosH);
		dlg.m_pDosHdr = AnalPE.pDosH;
	}
	if (AnalPE.pOptH64 != NULL) {
		dlg.m_dwResRootRva = AnalPE.pOptH64->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress;
		dlg.m_pResRoot = (IMAGE_RESOURCE_DIRECTORY*)(dlg.m_dwResRootRva + (DWORD)AnalPE.pDosH);
		dlg.m_pDosHdr = AnalPE.pDosH;
	}


	dlg.DoModal();
}


void CatalogDlg::OnBnClickedButton20()
{
	// TODO: 在此添加控件通知处理程序代码

	if (AnalPE.buf == NULL)
	{
		AfxMessageBox(L"请拖入PE文件");
		return;
	}
	RelocationDlg dlg;
	dlg.DoModal();
}


BOOL CatalogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ShowPeInfo();//显示界面
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CatalogDlg::OnBnClickedButton21()
{
	// TODO: 在此添加控件通知处理程序代码
	//TLSTableDlg tls;
	//tls.m_pDosHdr = AnalPE.pDosH;

	//if (AnalPE.pOptH != NULL) {
	//	tls.dwTls = AnalPE.pOptH->DataDirectory[9].VirtualAddress;
	//}
	//if (AnalPE.pOptH64 != NULL) {
	//	tls.dwTls = AnalPE.pOptH64->DataDirectory[9].VirtualAddress;
	//}

	//tls.DoModal();

	TLSTableDlg* pTLS = new TLSTableDlg(AnalPE.pDosH, AnalPE.pNtH);
	pTLS->DoModal();

}


void CatalogDlg::OnBnClickedButton22()
{
	// TODO: 在此添加控件通知处理程序代码
	DelayTableDlg pDelayInfo;
	pDelayInfo.DoModal();
}

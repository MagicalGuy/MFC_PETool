// DelayTableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool_Tang.h"
#include "DelayTableDlg.h"
#include "afxdialogex.h"


// DelayTableDlg 对话框

IMPLEMENT_DYNAMIC(DelayTableDlg, CDialogEx)

DelayTableDlg::DelayTableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DelayTable, pParent)
{

}

DelayTableDlg::~DelayTableDlg()
{
}

void DelayTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListDelayDll);
	DDX_Control(pDX, IDC_LIST3, m_ListDelayFun);
}


BEGIN_MESSAGE_MAP(DelayTableDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &DelayTableDlg::OnNMClickList1)
END_MESSAGE_MAP()


// DelayTableDlg 消息处理程序


DWORD DelayTableDlg::RVA2FO(DWORD dwRva)
{
	//文件对齐与内存对齐相等
	if (AnalPE.pNtH->OptionalHeader.FileAlignment == AnalPE.pNtH->OptionalHeader.SectionAlignment)
	{
		return dwRva;
	}
	//区段头
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(AnalPE.pNtH);

	//循环查找
	for (int i = 0; i < AnalPE.pNtH->FileHeader.NumberOfSections; i++)
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





void DelayTableDlg::GetDelayDllInfo()
{
	PBYTE pBuf = (PBYTE)AnalPE.pDosH;
	DWORD dwFO = RVA2FO(AnalPE.pDatD[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress);
	PIMAGE_DELAYLOAD_DESCRIPTOR pDelay = (PIMAGE_DELAYLOAD_DESCRIPTOR)(pBuf + dwFO);

	//循环查找
	while (pDelay->DllNameRVA)
	{
		m_DelayDllName = (CHAR*)(pBuf + RVA2FO(pDelay->DllNameRVA));
		m_DelayINT.Format(L"%p", RVA2FO(pDelay->ImportAddressTableRVA));
		m_DelayIAT.Format(L"%p", RVA2FO(pDelay->ImportNameTableRVA));

		m_ListDelayDll.AddItem(3, m_DelayDllName, m_DelayINT, m_DelayIAT);
		pDelay++;
	}
}

void DelayTableDlg::GetDelayFunInfo()
{
	m_ListDelayFun.DeleteAllItems();

	PBYTE pBuf = (PBYTE)AnalPE.pDosH;

	//循环查找
	while (m_pDelayThunk->u1.AddressOfData)
	{
		//序号命名
		if (IMAGE_SNAP_BY_ORDINAL32(m_pDelayThunk->u1.Ordinal))
		{
			m_DelayFunOrdinal.Format(L"%X", IMAGE_ORDINAL32(m_pDelayThunk->u1.Ordinal));
			m_DelayFunName = L"--";
		}
		//名称命名
		else
		{
			PIMAGE_IMPORT_BY_NAME pName = (PIMAGE_IMPORT_BY_NAME)(pBuf +
				RVA2FO(m_pDelayThunk->u1.AddressOfData));

			m_DelayFunOrdinal.Format(L"%X", pName->Hint);
			m_DelayFunName = (CHAR*)pName->Name;
		}
		m_ListDelayFun.AddItem(2, m_DelayFunOrdinal, m_DelayFunName);
		m_pDelayThunk++;
	}
}

void DelayTableDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//获取选中数据
	int nSel = m_ListDelayDll.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"请选中数据");
		return;
	}

	//获取序号
	int  dwINTF0 = wcstoll(m_ListDelayDll.GetItemText(nSel, 2), NULL, 16);

	if (dwINTF0 == -1)
	{
		dwINTF0 = wcstoll(m_ListDelayDll.GetItemText(nSel, 1), NULL, 16);
	}

	if (dwINTF0 == -1)
	{
		return;
	}

	//转换
	m_pDelayThunk = (PIMAGE_THUNK_DATA32)((PBYTE)AnalPE.pDosH + dwINTF0);

	//获取函数信息
	GetDelayFunInfo();

	*pResult = 0;
}


BOOL DelayTableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListDelayDll.AddColumn(3, L"DllName", 150, L"TNT(FO)", 100, L"IAT(FO)", 100);

	GetDelayDllInfo();

	m_ListDelayFun.AddColumn(2, L"FunOrdinal", 80, L"FunName", 170);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

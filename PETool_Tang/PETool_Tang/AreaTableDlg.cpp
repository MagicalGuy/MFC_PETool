// AreaTableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool_Tang.h"
#include "AreaTableDlg.h"
#include "afxdialogex.h"


// AreaTableDlg 对话框

IMPLEMENT_DYNAMIC(AreaTableDlg, CDialogEx)

AreaTableDlg::AreaTableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AreaTable, pParent)
{

}

AreaTableDlg::~AreaTableDlg()
{
}

void AreaTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_AreaTabList);
}


BEGIN_MESSAGE_MAP(AreaTableDlg, CDialogEx)
END_MESSAGE_MAP()


// AreaTableDlg 消息处理程序


void AreaTableDlg::ShowAreaTable()
{
	if (AnalPE.pSecH == NULL)
	{
		return;
	}
	PIMAGE_SECTION_HEADER pSecHTemp = AnalPE.pSecH;;//区段头
	int i = 0;
	CString str;

	while (i < AnalPE.pNtH->FileHeader.NumberOfSections)	//区段数目
	{
		str = pSecHTemp->Name;
		m_AreaTabList.InsertItem(i, str);
		str.Format(L"%08X", pSecHTemp->VirtualAddress);
		m_AreaTabList.SetItemText(i, 1, str);
		str.Format(L"%08X", pSecHTemp->Misc.VirtualSize);
		m_AreaTabList.SetItemText(i, 2, str);
		str.Format(L"%08X", pSecHTemp->PointerToRawData);
		m_AreaTabList.SetItemText(i, 3, str);
		str.Format(L"%08X", pSecHTemp->SizeOfRawData);
		m_AreaTabList.SetItemText(i, 4, str);
		str.Format(L"%08X", pSecHTemp->Characteristics);
		m_AreaTabList.SetItemText(i, 5, str);
		++pSecHTemp;
		i++;
	}
}

BOOL AreaTableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CString str[] = { L"名称",L"VOffset",L"VSize",L"ROffset",L"Rsize",L"标志" };
	for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	{
		m_AreaTabList.InsertColumn(i, str[i], LVCFMT_LEFT, 67);
	}
	ShowAreaTable();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE

}

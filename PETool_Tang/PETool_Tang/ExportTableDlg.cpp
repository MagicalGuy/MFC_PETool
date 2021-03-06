// ExportTableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PETool_Tang.h"
#include "ExportTableDlg.h"
#include "afxdialogex.h"
using namespace std;
#include<string>


// ExportTableDlg 对话框

IMPLEMENT_DYNAMIC(ExportTableDlg, CDialogEx)

ExportTableDlg::ExportTableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ExportTable, pParent)
	, m_ExportOffest(_T(""))
	, m_Characteristic(_T(""))
	, m_Plot(_T(""))
	, m_Name(_T(""))
	, m_NameString(_T(""))
	, m_FunctionNumber(_T(""))
	, m_FunctionNameNumber(_T(""))
	, m_FunctionAddr(_T(""))
	, m_FunctionNameAddr(_T(""))
	, m_FunSerialNumberAddr(_T(""))
{

}

ExportTableDlg::~ExportTableDlg()
{
}

void ExportTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ExportOffest);
	DDX_Text(pDX, IDC_EDIT2, m_Characteristic);
	DDX_Text(pDX, IDC_EDIT3, m_Plot);
	DDX_Text(pDX, IDC_EDIT4, m_Name);
	DDX_Text(pDX, IDC_EDIT5, m_NameString);
	DDX_Text(pDX, IDC_EDIT6, m_FunctionNumber);
	DDX_Text(pDX, IDC_EDIT7, m_FunctionNameNumber);
	DDX_Text(pDX, IDC_EDIT8, m_FunctionAddr);
	DDX_Text(pDX, IDC_EDIT9, m_FunctionNameAddr);
	DDX_Text(pDX, IDC_EDIT10, m_FunSerialNumberAddr);
	DDX_Control(pDX, IDC_LIST1, m_ExportList);
}


BEGIN_MESSAGE_MAP(ExportTableDlg, CDialogEx)
END_MESSAGE_MAP()


// ExportTableDlg 消息处理程序
DWORD NumberOfFun;
DWORD NumberOfName;
PDWORD pFunAddr;
PDWORD pFunNameAddr;
PWORD pOrdinalAddr;

void ExportTableDlg::ShowExportInfo()
{
	//函数偏移表地址：
	AnalPE.OutPutPeInfo(m_ExportOffest, AnalPE.CalcOffset(AnalPE.pDatD->VirtualAddress));
	//函数地址：
	AnalPE.OutPutPeInfo(m_FunctionAddr, AnalPE.pExpD->AddressOfFunctions);
	//函数名序号地址：
	AnalPE.OutPutPeInfo(m_FunSerialNumberAddr, AnalPE.pExpD->AddressOfNameOrdinals);
	//函数名称地址：
	AnalPE.OutPutPeInfo(m_FunctionNameAddr, AnalPE.pExpD->AddressOfNames);
	//基址：
	AnalPE.OutPutPeInfo(m_Plot, AnalPE.CalcOffset(AnalPE.pExpD->Base));
	//特征值：
	AnalPE.OutPutPeInfo(m_Characteristic, AnalPE.CalcOffset(AnalPE.pExpD->Characteristics));
	//名称：
	AnalPE.OutPutPeInfo(m_Name, AnalPE.CalcOffset(AnalPE.pExpD->Name));

	//名称字串：
	m_NameString = AnalPE.PeFileName;
	int i = m_NameString.ReverseFind('\\');
	m_NameString.Delete(0, i + 1);
	//("函数数量：
	AnalPE.OutPutPeInfo(m_FunctionNumber, AnalPE.CalcOffset(AnalPE.pExpD->NumberOfFunctions));
	//函数名数量：
	AnalPE.OutPutPeInfo(m_FunctionNameNumber, AnalPE.CalcOffset(AnalPE.pExpD->NumberOfNames));
	UpdateData(FALSE);
}

void ExportTableDlg::ShowExportList()
{
	CString str[] = { L"序号",L"RVA",L"偏移",L"函数" };
	for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	{
		m_ExportList.InsertColumn(i, str[i], LVCFMT_LEFT, 67);
	}
	for (DWORD i = 0; i < NumberOfFun; i++)
	{
		//如果是无效函数 进行下一次
		if (!pFunAddr[i])
		{
			continue;
		}
		//此时为有效函数  在序号表查找是否有这个序号 用以判断是函数名导出,函数序号导出
		DWORD j = 0;
		CString str;
		for (; j < NumberOfName; j++)
		{

			if (i == pOrdinalAddr[j])
			{
				break;
			}
		}

		//函数名导出的函数
		if (j != NumberOfName)
		{
			//printf_s("序号：%d  ",pOrdinalAddr[j]+AnalPE.pExpD->Base);
			str.Format(L"%08X", pOrdinalAddr[j] + AnalPE.pExpD->Base);
			m_ExportList.InsertItem(i, str);
			//printf_s("RVA：%08X  ",pFunAddr[i]);
			str.Format(L"%08X", pFunAddr[i]);
			m_ExportList.SetItemText(i, 1, str);
			//printf_s("偏移：%08X  ",AnalPE.CalcOffset(pFunAddr[i]));
			str.Format(L"%08X", AnalPE.CalcOffset(pFunAddr[i]));
			m_ExportList.SetItemText(i, 2, str);
			//	printf_s("函数名：%s\n",(AnalPE.buf+AnalPE.CalcOffset(pFunNameAddr[j])));
		//	DWORD temp = (DWORD)(AnalPE.buf + AnalPE.CalcOffset(pFunNameAddr[j]));
			CString str((AnalPE.buf + AnalPE.CalcOffset(pFunNameAddr[j])));
			//str=temp;		
			m_ExportList.SetItemText(i, 3, str);
		}
		//序号导出的函数 没有名字
		else
		{
			//printf_s("%d",i+AnalPE.pExpD->Base);
			str.Format(L"%08X", i + AnalPE.pExpD->Base);
			m_ExportList.InsertItem(i, str);
			m_ExportList.SetItemText(i, 1, L"-");
			m_ExportList.SetItemText(i, 2, L"-");
			//CString str1(AnalPE.buf + AnalPE.CalcOffset(pFunNameAddr[i]));
			//string   str2 = CStringA(str1);
			//const char* p =str2.c_str();
			//if (strcmp(p, "") == 0)
			//{
			//	//没有
			//	m_ExportList.SetItemText(i, 3, L"-");
			//}
			m_ExportList.SetItemText(i, 3, L"-");

		}
	}
}

BOOL ExportTableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//获取数据目录

	if (AnalPE.pOptH!=NULL) {
		AnalPE.pDatD = &(AnalPE.pOptH->DataDirectory[0]);
	}
	if (AnalPE.pOptH64!=NULL) {	
		AnalPE.pDatD = &(AnalPE.pOptH64->DataDirectory[0]);
	}
	
	//获取导出表数据
	AnalPE.pExpD = (PIMAGE_EXPORT_DIRECTORY)(AnalPE.buf + AnalPE.CalcOffset(AnalPE.pDatD->VirtualAddress));
	//判断是否有导出函数

	//取出三个表的函数地址
	pFunAddr = (PDWORD)(AnalPE.buf + AnalPE.CalcOffset(AnalPE.pExpD->AddressOfFunctions));	//函数地址
	pFunNameAddr = (PDWORD)(AnalPE.buf + AnalPE.CalcOffset(AnalPE.pExpD->AddressOfNames));	//函数名地址
	pOrdinalAddr = (PWORD)(AnalPE.buf + AnalPE.CalcOffset(AnalPE.pExpD->AddressOfNameOrdinals));//函数序号地址

	NumberOfFun = AnalPE.pExpD->NumberOfFunctions; //函数数量
	NumberOfName = AnalPE.pExpD->AddressOfNames;	//函数名称数量
	ShowExportInfo();
	ShowExportList();
	return TRUE;  // return TRUE unless you set the focus to a control

				  // 异常: OCX 属性页应返回 FALSE
}

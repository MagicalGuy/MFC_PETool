// ExportTableDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool_Tang.h"
#include "ExportTableDlg.h"
#include "afxdialogex.h"
using namespace std;
#include<string>


// ExportTableDlg �Ի���

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


// ExportTableDlg ��Ϣ�������
DWORD NumberOfFun;
DWORD NumberOfName;
PDWORD pFunAddr;
PDWORD pFunNameAddr;
PWORD pOrdinalAddr;

void ExportTableDlg::ShowExportInfo()
{
	//����ƫ�Ʊ��ַ��
	AnalPE.OutPutPeInfo(m_ExportOffest, AnalPE.CalcOffset(AnalPE.pDatD->VirtualAddress));
	//������ַ��
	AnalPE.OutPutPeInfo(m_FunctionAddr, AnalPE.pExpD->AddressOfFunctions);
	//��������ŵ�ַ��
	AnalPE.OutPutPeInfo(m_FunSerialNumberAddr, AnalPE.pExpD->AddressOfNameOrdinals);
	//�������Ƶ�ַ��
	AnalPE.OutPutPeInfo(m_FunctionNameAddr, AnalPE.pExpD->AddressOfNames);
	//��ַ��
	AnalPE.OutPutPeInfo(m_Plot, AnalPE.CalcOffset(AnalPE.pExpD->Base));
	//����ֵ��
	AnalPE.OutPutPeInfo(m_Characteristic, AnalPE.CalcOffset(AnalPE.pExpD->Characteristics));
	//���ƣ�
	AnalPE.OutPutPeInfo(m_Name, AnalPE.CalcOffset(AnalPE.pExpD->Name));

	//�����ִ���
	m_NameString = AnalPE.PeFileName;
	int i = m_NameString.ReverseFind('\\');
	m_NameString.Delete(0, i + 1);
	//("����������
	AnalPE.OutPutPeInfo(m_FunctionNumber, AnalPE.CalcOffset(AnalPE.pExpD->NumberOfFunctions));
	//������������
	AnalPE.OutPutPeInfo(m_FunctionNameNumber, AnalPE.CalcOffset(AnalPE.pExpD->NumberOfNames));
	UpdateData(FALSE);
}

void ExportTableDlg::ShowExportList()
{
	CString str[] = { L"���",L"RVA",L"ƫ��",L"����" };
	for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	{
		m_ExportList.InsertColumn(i, str[i], LVCFMT_LEFT, 67);
	}
	for (DWORD i = 0; i < NumberOfFun; i++)
	{
		//�������Ч���� ������һ��
		if (!pFunAddr[i])
		{
			continue;
		}
		//��ʱΪ��Ч����  ����ű�����Ƿ��������� �����ж��Ǻ���������,������ŵ���
		DWORD j = 0;
		CString str;
		for (; j < NumberOfName; j++)
		{

			if (i == pOrdinalAddr[j])
			{
				break;
			}
		}

		//�����������ĺ���
		if (j != NumberOfName)
		{
			//printf_s("��ţ�%d  ",pOrdinalAddr[j]+AnalPE.pExpD->Base);
			str.Format(L"%08X", pOrdinalAddr[j] + AnalPE.pExpD->Base);
			m_ExportList.InsertItem(i, str);
			//printf_s("RVA��%08X  ",pFunAddr[i]);
			str.Format(L"%08X", pFunAddr[i]);
			m_ExportList.SetItemText(i, 1, str);
			//printf_s("ƫ�ƣ�%08X  ",AnalPE.CalcOffset(pFunAddr[i]));
			str.Format(L"%08X", AnalPE.CalcOffset(pFunAddr[i]));
			m_ExportList.SetItemText(i, 2, str);
			//	printf_s("��������%s\n",(AnalPE.buf+AnalPE.CalcOffset(pFunNameAddr[j])));
		//	DWORD temp = (DWORD)(AnalPE.buf + AnalPE.CalcOffset(pFunNameAddr[j]));
			CString str((AnalPE.buf + AnalPE.CalcOffset(pFunNameAddr[j])));
			//str=temp;		
			m_ExportList.SetItemText(i, 3, str);
		}
		//��ŵ����ĺ��� û������
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
			//	//û��
			//	m_ExportList.SetItemText(i, 3, L"-");
			//}
			m_ExportList.SetItemText(i, 3, L"-");

		}
	}
}

BOOL ExportTableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//��ȡ����Ŀ¼

	if (AnalPE.pOptH!=NULL) {
		AnalPE.pDatD = &(AnalPE.pOptH->DataDirectory[0]);
	}
	if (AnalPE.pOptH64!=NULL) {	
		AnalPE.pDatD = &(AnalPE.pOptH64->DataDirectory[0]);
	}
	
	//��ȡ����������
	AnalPE.pExpD = (PIMAGE_EXPORT_DIRECTORY)(AnalPE.buf + AnalPE.CalcOffset(AnalPE.pDatD->VirtualAddress));
	//�ж��Ƿ��е�������

	//ȡ��������ĺ�����ַ
	pFunAddr = (PDWORD)(AnalPE.buf + AnalPE.CalcOffset(AnalPE.pExpD->AddressOfFunctions));	//������ַ
	pFunNameAddr = (PDWORD)(AnalPE.buf + AnalPE.CalcOffset(AnalPE.pExpD->AddressOfNames));	//��������ַ
	pOrdinalAddr = (PWORD)(AnalPE.buf + AnalPE.CalcOffset(AnalPE.pExpD->AddressOfNameOrdinals));//������ŵ�ַ

	NumberOfFun = AnalPE.pExpD->NumberOfFunctions; //��������
	NumberOfName = AnalPE.pExpD->AddressOfNames;	//������������
	ShowExportInfo();
	ShowExportList();
	return TRUE;  // return TRUE unless you set the focus to a control

				  // �쳣: OCX ����ҳӦ���� FALSE
}

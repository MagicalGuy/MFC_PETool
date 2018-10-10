// DelayTableDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool_Tang.h"
#include "DelayTableDlg.h"
#include "afxdialogex.h"


// DelayTableDlg �Ի���

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


// DelayTableDlg ��Ϣ�������


DWORD DelayTableDlg::RVA2FO(DWORD dwRva)
{
	//�ļ��������ڴ�������
	if (AnalPE.pNtH->OptionalHeader.FileAlignment == AnalPE.pNtH->OptionalHeader.SectionAlignment)
	{
		return dwRva;
	}
	//����ͷ
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(AnalPE.pNtH);

	//ѭ������
	for (int i = 0; i < AnalPE.pNtH->FileHeader.NumberOfSections; i++)
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





void DelayTableDlg::GetDelayDllInfo()
{
	PBYTE pBuf = (PBYTE)AnalPE.pDosH;
	DWORD dwFO = RVA2FO(AnalPE.pDatD[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress);
	PIMAGE_DELAYLOAD_DESCRIPTOR pDelay = (PIMAGE_DELAYLOAD_DESCRIPTOR)(pBuf + dwFO);

	//ѭ������
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

	//ѭ������
	while (m_pDelayThunk->u1.AddressOfData)
	{
		//�������
		if (IMAGE_SNAP_BY_ORDINAL32(m_pDelayThunk->u1.Ordinal))
		{
			m_DelayFunOrdinal.Format(L"%X", IMAGE_ORDINAL32(m_pDelayThunk->u1.Ordinal));
			m_DelayFunName = L"--";
		}
		//��������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡѡ������
	int nSel = m_ListDelayDll.GetSelectionMark();
	if (nSel < 0)
	{
		MessageBox(L"��ѡ������");
		return;
	}

	//��ȡ���
	int  dwINTF0 = wcstoll(m_ListDelayDll.GetItemText(nSel, 2), NULL, 16);

	if (dwINTF0 == -1)
	{
		dwINTF0 = wcstoll(m_ListDelayDll.GetItemText(nSel, 1), NULL, 16);
	}

	if (dwINTF0 == -1)
	{
		return;
	}

	//ת��
	m_pDelayThunk = (PIMAGE_THUNK_DATA32)((PBYTE)AnalPE.pDosH + dwINTF0);

	//��ȡ������Ϣ
	GetDelayFunInfo();

	*pResult = 0;
}


BOOL DelayTableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListDelayDll.AddColumn(3, L"DllName", 150, L"TNT(FO)", 100, L"IAT(FO)", 100);

	GetDelayDllInfo();

	m_ListDelayFun.AddColumn(2, L"FunOrdinal", 80, L"FunName", 170);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

// RelocationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool_Tang.h"
#include "RelocationDlg.h"
#include "afxdialogex.h"
#include <vector>
using namespace std;

// RelocationDlg �Ի���

vector<PIMAGE_BASE_RELOCATION> m_VecpBseRInfo;
DWORD v;
/***************-�ض�λ��-*****************/
//��һ����Ա������
typedef struct _RELOCINFO
{
	DWORD dwRelocRVA;		//��Ҫ�ض�λ����������ַ
	DWORD dwOffset;			//������������ַ������ļ�����
	BYTE bType;				//�ض�λ��ʽ
	DWORD dwRelocValue;		//��������ļ�ƫ��ȡ�������� ������ݾ��������ַ��VA��
	BYTE bData[10];			//�øղŵĵ�ַ��VA����ȥ��ַ�õ���������ַRVA �������ļ�ƫ�� �����е�����ȡ�� �ŵ��������
}RELOCINFO, *PRELOCINFO;
//�ڶ�����Ա������
typedef struct _RELOCAREAINFO
{
	CHAR szSectionName[8];  //�������ڵĽ���
	DWORD dwAreaRVA;		//�����ַ
	DWORD NumberOfReloc;	//��������ض�λ�ľ������
	std::vector<RELOCINFO> VecRelocInfo;//��������ض�λ�ľ�����Ϣ
}RELOCAREAINFO, *PRELOCAREAINFO;
vector<RELOCAREAINFO> m_VecRelocAreaInfo;
//��������Ա������
typedef struct _TYPEOFFSET
{
	WORD Offset : 12;		//ƫ��ֵ
	WORD Type : 4;		//�ض�λ���ԣ���ʽ��
}TYPEOFFSET, *PTYPEOFFSET;


//�ض�λ��Ҫ ��������΢��Щ��ͬ
DWORD RelCalcOffset(DWORD Rva, PIMAGE_NT_HEADERS32 pNtH, char *Tempbuf, PCHAR pName = NULL, PCHAR pData = NULL, int Flag = NULL)
{
	//PIMAGE_NT_HEADERS32 pnt=pNtH;
	PIMAGE_SECTION_HEADER pSecHTemp = IMAGE_FIRST_SECTION(pNtH);//����ͷ
	int index = 0;

	while (!(Rva >= pSecHTemp->VirtualAddress&&
		Rva < pSecHTemp->VirtualAddress + pSecHTemp->SizeOfRawData))
	{
		//�����������λ�û���ҵ�
		if (index > pNtH->FileHeader.NumberOfSections)
		{
			//	m_Section=L"����";
			////	DWORD a[5];
			//	_memccpy(&Address,pSecHTemp,6,24);
			//	//Address=(int);
			if (Flag == 2)
			{
				return Rva - pNtH->OptionalHeader.ImageBase;
			}
			return Rva;
		}
		++index;
		++pSecHTemp;
	}
	//��ȡ������
	if (pName != NULL)
	{
		//return Rva-pNtH->OptionalHeader.ImageBase;
		memcpy(pName, pSecHTemp->Name, 8);
	}
	v = Rva - pSecHTemp->VirtualAddress + pSecHTemp->PointerToRawData;;
	DWORD iiii = (long)Tempbuf + v;
	//��ȡ����
	if (pData != NULL)
	{
		//if (Flag==NULL)
		//{
		//	return Rva-pNtH->OptionalHeader.ImageBase;
		//}
		if (Flag == 2)
		{
			return Rva - pNtH->OptionalHeader.ImageBase;
		}
		//flag Ϊ1ʱ 
		memcpy(pData, PCHAR((long)Tempbuf + v), 10);
	}
	return v;
}


IMPLEMENT_DYNAMIC(RelocationDlg, CDialogEx)

RelocationDlg::RelocationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Relocation, pParent)
{

}

RelocationDlg::~RelocationDlg()
{
}

void RelocationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_FirstReloc);
	DDX_Control(pDX, IDC_LIST2, m_SecondReloc);
}


BEGIN_MESSAGE_MAP(RelocationDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &RelocationDlg::OnNMClickList1)
END_MESSAGE_MAP()


// RelocationDlg ��Ϣ�������


void RelocationDlg::ShowRelocation()
{
	if (AnalPE.pOptH != NULL) {
		AnalPE.pDatD = &(AnalPE.pOptH->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC]);//Ҳ����5
	}
	if (AnalPE.pOptH64 != NULL) {
		AnalPE.pDatD = &(AnalPE.pOptH64->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC]);//Ҳ����5
	}


	if (AnalPE.pDatD->Size == 0) {
		MessageBox(L"û���ض�λ��");
		return;
	}

	PIMAGE_BASE_RELOCATION pBasR = (PIMAGE_BASE_RELOCATION)((long)AnalPE.buf + AnalPE.CalcOffset(AnalPE.pDatD->VirtualAddress));
	RELOCAREAINFO Temp = { 0 };
	int j = 0;//����
	CString str;
	while (pBasR->VirtualAddress)
	{
		//printf_s("������%d  ",j);
		str.Format(L"%d", j + 1);
		m_FirstReloc.InsertItem(j, str);
		//����������ַ������ȡ�������ط�
		Temp.dwAreaRVA = pBasR->VirtualAddress;

		RelCalcOffset(Temp.dwAreaRVA, AnalPE.pNtH, AnalPE.buf, Temp.szSectionName, NULL);
		//	printf_s("%s   ",Temp.szSectionName);
		CString str(Temp.szSectionName);
		m_FirstReloc.SetItemText(j, 1, str);
		//printf_s("%08X   ",pBasR->VirtualAddress);
		str.Format(L"%08X", pBasR->VirtualAddress);
		m_FirstReloc.SetItemText(j, 2, str);
		Temp.NumberOfReloc = (pBasR->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2;
		//	printf_s("%02X  %d\n", Temp.NumberOfReloc, Temp.NumberOfReloc);
		str.Format(L"%02X", Temp.NumberOfReloc);
		CString str1;
		str1.Format(L"%d", Temp.NumberOfReloc);
		m_FirstReloc.SetItemText(j, 3, str + L" " + str1);
		//dwCount=Temp.NumberOfReloc;

		m_VecpBseRInfo.push_back(pBasR);
		//��һ�������ض�λ��Ϣ���
		m_VecRelocAreaInfo.push_back(Temp);
		pBasR = (PIMAGE_BASE_RELOCATION)((long)pBasR + pBasR->SizeOfBlock);
		j++;
	}
	int i = 0;
}

void RelocationDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//*pResult = 0;


	POSITION pos = m_FirstReloc.GetFirstSelectedItemPosition();
	int nIndex = (int)pos;
	if (pos == NULL)//�ж��Ƿ�Ϊ��
	{
		return;
	}
	m_SecondReloc.DeleteAllItems();
	int i = 0;
	CString str;

	//�õ���������Ա��TYPEOFFEST��ʼλ�� ֮��ʼѭ����ȡ�ض�λ��Ϣ
	PTYPEOFFSET pOffset = (PTYPEOFFSET)((long)m_VecpBseRInfo[nIndex - 1] + sizeof(IMAGE_BASE_RELOCATION));
	int z = m_VecRelocAreaInfo[nIndex - 1].NumberOfReloc;
	for (DWORD i = 0; i < m_VecRelocAreaInfo[nIndex - 1].NumberOfReloc; i++)
	{
		//printf_s("������%d  ",i);
		str.Format(L"%d", i + 1);
		m_SecondReloc.InsertItem(i, str);
		RELOCINFO RelocInfoTemp = { 0 };
		//��Ҫ�ض�λ�������ַ��RVA��
		RelocInfoTemp.dwRelocRVA = m_VecRelocAreaInfo[nIndex - 1].dwAreaRVA + pOffset->Offset;
		//	printf_s("RVA��%08X  ", RelocInfoTemp.dwRelocRVA);
		str.Format(L"%08X", RelocInfoTemp.dwRelocRVA);
		m_SecondReloc.SetItemText(i, 1, str);
		//������������ַ������ļ�ƫ��
		RelocInfoTemp.dwOffset = RelCalcOffset(RelocInfoTemp.dwRelocRVA, AnalPE.pNtH, NULL, NULL);
		//	printf_s("ƫ�ƣ�%08X  ", RelocInfoTemp.dwOffset);
		str.Format(L"%08X", RelocInfoTemp.dwOffset);
		m_SecondReloc.SetItemText(i, 2, str);
		//�ض�λ��ʽ
		RelocInfoTemp.bType = pOffset->Type;
		//printf_s("���ͣ�HIGHLOW (%d)  ",RelocInfoTemp.bType);
		str.Format(L"HIGHLOW (%d)", RelocInfoTemp.bType);
		m_SecondReloc.SetItemText(i, 3, str);
		//��������ļ�ƫ��ȡ�������� ������ݾ�����Ҫ�ض�λ�������ַ(VA)
		RelocInfoTemp.dwRelocValue = *(PDWORD)((long)AnalPE.buf + RelocInfoTemp.dwOffset);
		//printf_s("FAR��ַ��%08X  ",RelocInfoTemp.dwRelocValue);
		str.Format(L"%08X", RelocInfoTemp.dwRelocValue);
		m_SecondReloc.SetItemText(i, 4, str);
		//RelocInfoTemp.bData
		DWORD VA = RelCalcOffset(RelocInfoTemp.dwRelocValue, AnalPE.pNtH, AnalPE.buf, NULL, (PCHAR)RelocInfoTemp.bData, 2);
		RelCalcOffset(VA, AnalPE.pNtH, AnalPE.buf, NULL, (PCHAR)RelocInfoTemp.bData, 1);
		CString str1;
		CString str2;
		for (int j = 0; j < 10; j++)
		{
			//�ж��Ƿ�����Ч�ַ�32-126������
			if (32 <= (RelocInfoTemp.bData)[0] && (RelocInfoTemp.bData)[0] <= 126)
			{
				//printf_s("%c",(RelocInfoTemp.bData)[j]);

				str1.Format(L"%c", (RelocInfoTemp.bData)[j]);
				str2 += str1;
			}
			else
			{
				//printf_s("%02X ",(RelocInfoTemp.bData)[j]);
				str1.Format(L"%02X", (RelocInfoTemp.bData)[j]);
				str2 += L" " + str1;
			}
		}
		m_SecondReloc.SetItemText(i, 5, str2);
		pOffset++;
	}
}


BOOL RelocationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString str[] = { L"����",L"����",L"RVA",L"��Ŀ" };
	CString str1[] = { L"����",L"RVA",L"ƫ��",L"����",L"FAR ��ַ",L"���ݽ���" };
	m_FirstReloc.SetExtendedStyle(m_FirstReloc.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//��ѡ�з��
	m_SecondReloc.SetExtendedStyle(m_SecondReloc.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	int z = _countof(str1);
	//����Ӧ��С Ҫ���� �������� �ֶ�΢��
	for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++)
	{
		m_FirstReloc.InsertColumn(i, str[i], LVCFMT_LEFT, 67);
	}
	for (int i = 0; i < sizeof(str1) / sizeof(str1[0]); i++)
	{

		//�з�б��0
		if (i == _countof(str1) - 1)
		{
			m_SecondReloc.InsertColumn(i, str1[i], LVCFMT_LEFT, 200);
		}
		else
		{
			m_SecondReloc.InsertColumn(i, str1[i], LVCFMT_LEFT, 67);
		}
	}
	ShowRelocation();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

// FileLocationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool_Tang.h"
#include "FileLocationDlg.h"
#include "afxdialogex.h"


// FileLocationDlg �Ի���

IMPLEMENT_DYNAMIC(FileLocationDlg, CDialogEx)

FileLocationDlg::FileLocationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(FileLocation, pParent)
	, m_Va(_T(""))
	, m_Rva(_T(""))
	, m_Offset(_T(""))
	, m_Section(_T(""))
	, m_Byte(_T(""))
{

}

FileLocationDlg::~FileLocationDlg()
{
}

void FileLocationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Va);
	DDX_Text(pDX, IDC_EDIT2, m_Rva);
	DDX_Text(pDX, IDC_EDIT3, m_Offset);
	DDX_Text(pDX, IDC_EDIT4, m_Section);
	DDX_Text(pDX, IDC_EDIT5, m_Byte);
}


BEGIN_MESSAGE_MAP(FileLocationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &FileLocationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &FileLocationDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &FileLocationDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &FileLocationDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &FileLocationDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &FileLocationDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON4, &FileLocationDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// FileLocationDlg ��Ϣ�������


void FileLocationDlg::LockEdit(int EditId)
{
	CEdit *p1 = (CEdit *)GetDlgItem(IDC_EDIT1);
	CEdit *p2 = (CEdit *)GetDlgItem(IDC_EDIT2);
	CEdit *p3 = (CEdit *)GetDlgItem(IDC_EDIT3);
	CEdit *p4 = (CEdit *)GetDlgItem(IDC_EDIT4);
	CEdit *p5 = (CEdit *)GetDlgItem(IDC_EDIT5);
	p1->SetReadOnly(TRUE);
	p2->SetReadOnly(TRUE);
	p3->SetReadOnly(TRUE);
	p4->SetReadOnly(TRUE);
	p5->SetReadOnly(TRUE);
	switch (EditId)
	{
	case IDC_EDIT1:
		p1->SetReadOnly(FALSE);
		break;
	case IDC_EDIT2:
		p2->SetReadOnly(FALSE);
		break;
	case IDC_EDIT3:
		p3->SetReadOnly(FALSE);
		break;
	default:
		break;
	}
	p1->SetWindowText(_T(""));
	p2->SetWindowText(_T(""));
	p3->SetWindowText(_T(""));
}

void FileLocationDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LockEdit(IDC_EDIT1);
}


void FileLocationDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LockEdit(IDC_EDIT2);
}


void FileLocationDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LockEdit(IDC_EDIT3);
}


void FileLocationDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void FileLocationDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void FileLocationDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}

DWORD FileLocationDlg::ExclusiveCalcOffset(DWORD Rva)
{
	//ѭ���Ƚ����Ǹ�����  ����������ξͼ���ѭ��  
	//PIMAGE_NT_HEADERS32 pnt=pNtH;
	PIMAGE_SECTION_HEADER pSecHTemp = IMAGE_FIRST_SECTION(AnalPE.pNtH);//����ͷ
	int index = 0;
	while (!(Rva >= pSecHTemp->VirtualAddress&&
		Rva < pSecHTemp->VirtualAddress + pSecHTemp->SizeOfRawData))
	{
		//�����������λ�û���ҵ�
		if (index > AnalPE.pNtH->FileHeader.NumberOfSections)
		{
			m_Section = L"����";
			////	DWORD a[5];
			//	_memccpy(&Address,pSecHTemp,6,24);
			//	//Address=(int);			

			return Rva;
		}
		++index;
		++pSecHTemp;
	}
	PBYTE iiii = (PBYTE)(Rva - pSecHTemp->VirtualAddress + pSecHTemp->PointerToRawData + (long)AnalPE.buf);
	//CString aa;
	//ʮ�����Ʊ༭��Ҳ��������������
	for (int i = 0; i < 10; i++)
	{
		CString jj;
		jj.Format(L"%02x ", *(iiii++));
		m_Byte += jj;
	}
	m_Section = pSecHTemp->Name;
	return Rva - pSecHTemp->VirtualAddress + pSecHTemp->PointerToRawData;
}



DWORD FileLocationDlg::FoaToRva(DWORD dwFoa)
{

	//DWORD dwRva = 0;
	//if (dwFoa < AnalPE.pSecH[0].PointerToRawData)
	//{
	//	return dwFoa;
	//}

	//for (int i = 0; i < AnalPE.pNtH->FileHeader.NumberOfSections; i++)
	//{
	//	if (dwFoa >= AnalPE.pSecH[i].PointerToRawData && dwFoa <= AnalPE.pSecH[i].PointerToRawData + AnalPE.pSecH[i].SizeOfRawData)
	//	{
	//		dwRva = dwFoa - AnalPE.pSecH[i].PointerToRawData + AnalPE.pOptH->ImageBase;
	//		break;
	//	}
	//}
	//return dwRva;



	//ѭ���Ƚ����Ǹ�����  ����������ξͼ���ѭ��  
	//PIMAGE_NT_HEADERS32 pnt=pNtH;
	PIMAGE_SECTION_HEADER pSecHTemp = IMAGE_FIRST_SECTION(AnalPE.pNtH);//����ͷ
	int index = 0;
	while (!(dwFoa >= pSecHTemp->PointerToRawData&&
		dwFoa < pSecHTemp->PointerToRawData + pSecHTemp->SizeOfRawData))
	{
		//�����������λ�û���ҵ�
		if (index > AnalPE.pNtH->FileHeader.NumberOfSections)
		{
			m_Section = L"����";
			////	DWORD a[5];
			//	_memccpy(&Address,pSecHTemp,6,24);
			//	//Address=(int);			

			return dwFoa;
		}
		++index;
		++pSecHTemp;
	}

	return dwFoa + pSecHTemp->VirtualAddress - pSecHTemp->PointerToRawData;

}

void FileLocationDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	DWORD Value;
	//va  rva  foa  Ϊ��
	if (m_Va == L""&&m_Rva == L""&&m_Offset == L"")
	{
		return;
	}
	//va ��Ϊ��
	if (m_Va != L"")
	{
		Value = AnalPE.ChangeNumber(m_Va);

		AnalPE.OutPutPeInfo(m_Rva, Value - AnalPE.pOptH->ImageBase);//���rva

		DWORD ShowValue = ExclusiveCalcOffset(Value - AnalPE.pOptH->ImageBase);
		AnalPE.OutPutPeInfo(m_Offset, ShowValue);//���ƫ��
												 //ExclusiveCalcOffset()
		UpdateData(FALSE);

	}
	//rva  ��Ϊ��
	if (m_Rva != L"")
	{
		Value = AnalPE.ChangeNumber(m_Rva);
	}
	//ora  ��Ϊ��
	if (m_Offset != L"")
	{
		Value = AnalPE.ChangeNumber(m_Offset);
		DWORD showValue = FoaToRva(Value);
		AnalPE.OutPutPeInfo(m_Rva, showValue);
		AnalPE.OutPutPeInfo(m_Va, showValue + AnalPE.pOptH->ImageBase);
		UpdateData(false);
		return;
	}

	DWORD ShowValue = ExclusiveCalcOffset(Value);
	AnalPE.OutPutPeInfo(m_Va, Value + AnalPE.pOptH->ImageBase);//���VA
	//AnalPE.OutPutPeInfo(m_Va,Value+AnalPE.pNtH->OptionalHeader.ImageBase);//���VA
	AnalPE.OutPutPeInfo(m_Rva, Value);		//���RVA
	AnalPE.OutPutPeInfo(m_Offset, ShowValue);//���ƫ��
											 //ExclusiveCalcOffset()
	UpdateData(FALSE);
}

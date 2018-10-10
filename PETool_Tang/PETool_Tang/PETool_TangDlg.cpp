
// PETool_TangDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PETool_Tang.h"
#include "PETool_TangDlg.h"
#include "afxdialogex.h"
#include "FileLocationDlg.h"
#include "AreaTableDlg.h"
#include"CatalogDlg.h"
#include <iostream>
#include <ctime>
#include "time.h"  
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPETool_TangDlg �Ի���



CPETool_TangDlg::CPETool_TangDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PETOOL_TANG_DIALOG, pParent)
	, m_EntryPoint(_T(""))
	, m_ImageBase(_T(""))
	, m_SizeOfImage(_T(""))
	, m_BaseOfCode(_T(""))
	, m_BaseOfData(_T(""))
	, m_SectionAlignment(_T(""))
	, m_FileAlignment(_T(""))
	, m_Magic(_T(""))
	, m_Subsystem(_T(""))
	, m_NumberOfSections(_T(""))
	, m_TimeDateStamp(_T(""))
	, m_SizeOfHeaders(_T(""))
	, m_Characteristics(_T(""))
	, m_CheckSum(_T(""))
	, m_SizeOfOptionalHeader(_T(""))
	, m_NumberOfRvaAndSizes(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPETool_TangDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_EntryPoint);
	DDX_Text(pDX, IDC_EDIT2, m_ImageBase);
	DDX_Text(pDX, IDC_EDIT3, m_SizeOfImage);
	DDX_Text(pDX, IDC_EDIT4, m_BaseOfCode);
	DDX_Text(pDX, IDC_EDIT5, m_BaseOfData);
	DDX_Text(pDX, IDC_EDIT6, m_SectionAlignment);
	DDX_Text(pDX, IDC_EDIT7, m_FileAlignment);
	DDX_Text(pDX, IDC_EDIT8, m_Magic);
	DDX_Text(pDX, IDC_EDIT9, m_Subsystem);
	DDX_Text(pDX, IDC_EDIT10, m_NumberOfSections);
	DDX_Text(pDX, IDC_EDIT11, m_TimeDateStamp);
	DDX_Text(pDX, IDC_EDIT12, m_SizeOfHeaders);
	DDX_Text(pDX, IDC_EDIT13, m_Characteristics);
	DDX_Text(pDX, IDC_EDIT14, m_CheckSum);
	DDX_Text(pDX, IDC_EDIT15, m_SizeOfOptionalHeader);
	DDX_Text(pDX, IDC_EDIT16, m_NumberOfRvaAndSizes);
}

BEGIN_MESSAGE_MAP(CPETool_TangDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON14, &CPETool_TangDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CPETool_TangDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON12, &CPETool_TangDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CPETool_TangDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON11, &CPETool_TangDlg::OnBnClickedButton11)
END_MESSAGE_MAP()


// CPETool_TangDlg ��Ϣ�������

BOOL CPETool_TangDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	//�������ԱȨ����ҷ�ļ�;
	ChangeWindowMessageFilterEx(this->m_hWnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
	ChangeWindowMessageFilterEx(this->m_hWnd, 0x0049, MSGFLT_ALLOW, NULL);
	// 0x0049 == WM_COPYGLOBALDATA


	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPETool_TangDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPETool_TangDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPETool_TangDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CPETool_TangDlg::ShowPeInfo()
{
	//BaseOfCode;
	if (AnalPE.buf == NULL)
	{
		AfxMessageBox(L"������PE�ļ�");
		return;
	}

	if (AnalPE.pOptH != NULL) {
		AnalPE.OutPutPeInfo(m_EntryPoint, AnalPE.pOptH->AddressOfEntryPoint);		//��ڵ�
		AnalPE.OutPutPeInfo(m_ImageBase, AnalPE.pOptH->ImageBase);					//�����ַ
		AnalPE.OutPutPeInfo(m_SizeOfImage, AnalPE.pOptH->SizeOfImage);				//�����С
		AnalPE.OutPutPeInfo(m_BaseOfCode, AnalPE.pOptH->BaseOfCode);					//�����ַ
		AnalPE.OutPutPeInfo(m_BaseOfData, AnalPE.pOptH->BaseOfData);					//���ݻ�ַ
		AnalPE.OutPutPeInfo(m_SectionAlignment, AnalPE.pOptH->SectionAlignment);		//�����
		AnalPE.OutPutPeInfo(m_FileAlignment, AnalPE.pOptH->FileAlignment);			//�ļ������
		AnalPE.OutPutPeInfo(m_Magic, AnalPE.pOptH->Magic);							//��־��
																					//�ڶ���
		AnalPE.OutPutPeInfo(m_Subsystem, AnalPE.pOptH->Subsystem);					//��ϵͳ
		AnalPE.OutPutPeInfo(m_NumberOfSections, AnalPE.pNtH->FileHeader.NumberOfSections);			//������Ŀ
		AnalPE.OutPutPeInfo(m_TimeDateStamp, AnalPE.pNtH->FileHeader.TimeDateStamp);				//����ʱ���־
		AnalPE.OutPutPeInfo(m_SizeOfHeaders, AnalPE.pOptH->SizeOfHeaders);			//���״�С
		AnalPE.OutPutPeInfo(m_Characteristics, AnalPE.pNtH->FileHeader.Characteristics);			//����ֵ
		AnalPE.OutPutPeInfo(m_CheckSum, AnalPE.pOptH->CheckSum);						//У���
		AnalPE.OutPutPeInfo(m_SizeOfOptionalHeader, AnalPE.pNtH->FileHeader.SizeOfOptionalHeader);	//��ѡͷ����С
		AnalPE.OutPutPeInfo(m_NumberOfRvaAndSizes, AnalPE.pOptH->NumberOfRvaAndSizes);//RVA������С
	}

	if (AnalPE.pOptH64 != NULL) {
		AnalPE.OutPutPeInfo(m_EntryPoint, AnalPE.pOptH64->AddressOfEntryPoint);		//��ڵ�
		AnalPE.OutPutPeInfo(m_ImageBase, AnalPE.pOptH64->ImageBase);					//�����ַ
		AnalPE.OutPutPeInfo(m_SizeOfImage, AnalPE.pOptH64->SizeOfImage);				//�����С
		AnalPE.OutPutPeInfo(m_BaseOfCode, AnalPE.pOptH64->BaseOfCode);					//�����ַ
		//AnalPE.OutPutPeInfo(m_BaseOfData, AnalPE.pOptH64->BaseOfData);					//���ݻ�ַ
		AnalPE.OutPutPeInfo(m_SectionAlignment, AnalPE.pOptH64->SectionAlignment);		//�����
		AnalPE.OutPutPeInfo(m_FileAlignment, AnalPE.pOptH64->FileAlignment);			//�ļ������
		AnalPE.OutPutPeInfo(m_Magic, AnalPE.pOptH64->Magic);							//��־��
																					//�ڶ���
		AnalPE.OutPutPeInfo(m_Subsystem, AnalPE.pOptH64->Subsystem);					//��ϵͳ
		AnalPE.OutPutPeInfo(m_NumberOfSections, AnalPE.m_pFileHdr->NumberOfSections);			//������Ŀ
		AnalPE.OutPutPeInfo(m_TimeDateStamp, AnalPE.m_pFileHdr->TimeDateStamp);				//����ʱ���־
		AnalPE.OutPutPeInfo(m_SizeOfHeaders, AnalPE.pOptH64->SizeOfHeaders);			//���״�С
		AnalPE.OutPutPeInfo(m_Characteristics, AnalPE.m_pFileHdr->Characteristics);			//����ֵ
		AnalPE.OutPutPeInfo(m_CheckSum, AnalPE.pOptH64->CheckSum);						//У���
		AnalPE.OutPutPeInfo(m_SizeOfOptionalHeader, AnalPE.m_pFileHdr->SizeOfOptionalHeader);	//��ѡͷ����С
		AnalPE.OutPutPeInfo(m_NumberOfRvaAndSizes, AnalPE.pOptH64->NumberOfRvaAndSizes);//RVA������С
	}


	UpdateData(FALSE);
}

void CPETool_TangDlg::OutPutPeInfo(CString &m_PeInfo, DWORD PeValue)
{
	CString str;
	str.Format(L"%08X", PeValue);//ת16����
	m_PeInfo = str;
	UpdateData(FALSE);
}



void CPETool_TangDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UINT movecount = DragQueryFile(hDropInfo, -1, NULL, 0);
	TCHAR movefile[MAX_PATH] = { 0 };
	for (UINT i = 0; i < movecount; i++)
	{

		DragQueryFile(hDropInfo, i, movefile, MAX_PATH);
		SetWindowText(movefile);
		//	UpdateData(FALSE);
	}
	DragFinish(hDropInfo);
	AnalPE.ObtainPeInfo(movefile);
	ShowPeInfo();
	CDialogEx::OnDropFiles(hDropInfo);
}


void CPETool_TangDlg::OnBnClickedButton14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	FileLocationDlg dlg;
	dlg.DoModal();
}


void CPETool_TangDlg::OnBnClickedButton15()
{

	time_t rawtime = AnalPE.m_pFileHdr->TimeDateStamp;
	struct tm info;
	//time(&rawtime);
	gmtime_s(&info, &rawtime);


	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//tm* FileTime = gmtime((time_t*)&AnalPE.m_pFileHdr->TimeDateStamp);

	CString time;
	time.Format(L"%d", info.tm_year + 1900);
	time.Append(L"-");
	time.AppendFormat(L"%d", (info.tm_mon + 1));
	time.Append(L"-");
	time.AppendFormat(L"%d", info.tm_mday);
	time.Append(L"  ");
	time.AppendFormat(L"%d", info.tm_hour);
	time.Append(L":");
	time.AppendFormat(L"%d", info.tm_min);
	time.Append(L":");
	time.AppendFormat(L"%d", info.tm_sec);

	MessageBox(time);

	//��ʽ��
	//time_t tick = (time_t)AnalPE.m_pFileHdr->TimeDateStamp;
	//struct tm tm;
	//char s[100];
	////time(&tick);
	//localtime_s(&tm,&tick);
	//strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);
	//MessageBox((CString )s);

}

//���α�
void CPETool_TangDlg::OnBnClickedButton12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (AnalPE.buf == NULL)
	{
		AfxMessageBox(L"������PE�ļ�");
		return;
	}
	AreaTableDlg dlg;
	dlg.DoModal();


}

//Ŀ¼��
void CPETool_TangDlg::OnBnClickedButton13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CatalogDlg dialog;
	dialog.DoModal();
}


void CPETool_TangDlg::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

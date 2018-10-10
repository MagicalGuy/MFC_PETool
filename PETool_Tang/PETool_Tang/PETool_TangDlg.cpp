
// PETool_TangDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPETool_TangDlg 对话框



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


// CPETool_TangDlg 消息处理程序

BOOL CPETool_TangDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	//允许管理员权限拖曳文件;
	ChangeWindowMessageFilterEx(this->m_hWnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
	ChangeWindowMessageFilterEx(this->m_hWnd, 0x0049, MSGFLT_ALLOW, NULL);
	// 0x0049 == WM_COPYGLOBALDATA


	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPETool_TangDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPETool_TangDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CPETool_TangDlg::ShowPeInfo()
{
	//BaseOfCode;
	if (AnalPE.buf == NULL)
	{
		AfxMessageBox(L"请拖入PE文件");
		return;
	}

	if (AnalPE.pOptH != NULL) {
		AnalPE.OutPutPeInfo(m_EntryPoint, AnalPE.pOptH->AddressOfEntryPoint);		//入口点
		AnalPE.OutPutPeInfo(m_ImageBase, AnalPE.pOptH->ImageBase);					//镜像地址
		AnalPE.OutPutPeInfo(m_SizeOfImage, AnalPE.pOptH->SizeOfImage);				//镜像大小
		AnalPE.OutPutPeInfo(m_BaseOfCode, AnalPE.pOptH->BaseOfCode);					//代码基址
		AnalPE.OutPutPeInfo(m_BaseOfData, AnalPE.pOptH->BaseOfData);					//数据基址
		AnalPE.OutPutPeInfo(m_SectionAlignment, AnalPE.pOptH->SectionAlignment);		//块对齐
		AnalPE.OutPutPeInfo(m_FileAlignment, AnalPE.pOptH->FileAlignment);			//文件块对齐
		AnalPE.OutPutPeInfo(m_Magic, AnalPE.pOptH->Magic);							//标志字
																					//第二版
		AnalPE.OutPutPeInfo(m_Subsystem, AnalPE.pOptH->Subsystem);					//子系统
		AnalPE.OutPutPeInfo(m_NumberOfSections, AnalPE.pNtH->FileHeader.NumberOfSections);			//区段数目
		AnalPE.OutPutPeInfo(m_TimeDateStamp, AnalPE.pNtH->FileHeader.TimeDateStamp);				//日期时间标志
		AnalPE.OutPutPeInfo(m_SizeOfHeaders, AnalPE.pOptH->SizeOfHeaders);			//部首大小
		AnalPE.OutPutPeInfo(m_Characteristics, AnalPE.pNtH->FileHeader.Characteristics);			//特征值
		AnalPE.OutPutPeInfo(m_CheckSum, AnalPE.pOptH->CheckSum);						//校验和
		AnalPE.OutPutPeInfo(m_SizeOfOptionalHeader, AnalPE.pNtH->FileHeader.SizeOfOptionalHeader);	//可选头部大小
		AnalPE.OutPutPeInfo(m_NumberOfRvaAndSizes, AnalPE.pOptH->NumberOfRvaAndSizes);//RVA数及大小
	}

	if (AnalPE.pOptH64 != NULL) {
		AnalPE.OutPutPeInfo(m_EntryPoint, AnalPE.pOptH64->AddressOfEntryPoint);		//入口点
		AnalPE.OutPutPeInfo(m_ImageBase, AnalPE.pOptH64->ImageBase);					//镜像地址
		AnalPE.OutPutPeInfo(m_SizeOfImage, AnalPE.pOptH64->SizeOfImage);				//镜像大小
		AnalPE.OutPutPeInfo(m_BaseOfCode, AnalPE.pOptH64->BaseOfCode);					//代码基址
		//AnalPE.OutPutPeInfo(m_BaseOfData, AnalPE.pOptH64->BaseOfData);					//数据基址
		AnalPE.OutPutPeInfo(m_SectionAlignment, AnalPE.pOptH64->SectionAlignment);		//块对齐
		AnalPE.OutPutPeInfo(m_FileAlignment, AnalPE.pOptH64->FileAlignment);			//文件块对齐
		AnalPE.OutPutPeInfo(m_Magic, AnalPE.pOptH64->Magic);							//标志字
																					//第二版
		AnalPE.OutPutPeInfo(m_Subsystem, AnalPE.pOptH64->Subsystem);					//子系统
		AnalPE.OutPutPeInfo(m_NumberOfSections, AnalPE.m_pFileHdr->NumberOfSections);			//区段数目
		AnalPE.OutPutPeInfo(m_TimeDateStamp, AnalPE.m_pFileHdr->TimeDateStamp);				//日期时间标志
		AnalPE.OutPutPeInfo(m_SizeOfHeaders, AnalPE.pOptH64->SizeOfHeaders);			//部首大小
		AnalPE.OutPutPeInfo(m_Characteristics, AnalPE.m_pFileHdr->Characteristics);			//特征值
		AnalPE.OutPutPeInfo(m_CheckSum, AnalPE.pOptH64->CheckSum);						//校验和
		AnalPE.OutPutPeInfo(m_SizeOfOptionalHeader, AnalPE.m_pFileHdr->SizeOfOptionalHeader);	//可选头部大小
		AnalPE.OutPutPeInfo(m_NumberOfRvaAndSizes, AnalPE.pOptH64->NumberOfRvaAndSizes);//RVA数及大小
	}


	UpdateData(FALSE);
}

void CPETool_TangDlg::OutPutPeInfo(CString &m_PeInfo, DWORD PeValue)
{
	CString str;
	str.Format(L"%08X", PeValue);//转16进制
	m_PeInfo = str;
	UpdateData(FALSE);
}



void CPETool_TangDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加控件通知处理程序代码
	FileLocationDlg dlg;
	dlg.DoModal();
}


void CPETool_TangDlg::OnBnClickedButton15()
{

	time_t rawtime = AnalPE.m_pFileHdr->TimeDateStamp;
	struct tm info;
	//time(&rawtime);
	gmtime_s(&info, &rawtime);


	// TODO: 在此添加控件通知处理程序代码
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

	//方式二
	//time_t tick = (time_t)AnalPE.m_pFileHdr->TimeDateStamp;
	//struct tm tm;
	//char s[100];
	////time(&tick);
	//localtime_s(&tm,&tick);
	//strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);
	//MessageBox((CString )s);

}

//区段表
void CPETool_TangDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	if (AnalPE.buf == NULL)
	{
		AfxMessageBox(L"请拖入PE文件");
		return;
	}
	AreaTableDlg dlg;
	dlg.DoModal();


}

//目录表
void CPETool_TangDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码

	CatalogDlg dialog;
	dialog.DoModal();
}


void CPETool_TangDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
}

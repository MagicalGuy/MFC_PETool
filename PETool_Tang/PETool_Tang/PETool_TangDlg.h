
// PETool_TangDlg.h : 头文件
//

#pragma once


// CPETool_TangDlg 对话框
class CPETool_TangDlg : public CDialogEx
{
	// 构造
public:
	CPETool_TangDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PETOOL_TANG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_EntryPoint;
	CString m_ImageBase;
	CString m_SizeOfImage;
	CString m_BaseOfCode;
	CString m_BaseOfData;
	CString m_SectionAlignment;
	CString m_FileAlignment;
	CString m_Magic;
	CString m_Subsystem;
	CString m_NumberOfSections;
	CString m_TimeDateStamp;
	CString m_SizeOfHeaders;
	CString m_Characteristics;
	CString m_CheckSum;
	CString m_SizeOfOptionalHeader;
	CString m_NumberOfRvaAndSizes;


	void ShowPeInfo();			//显示PE相关信息
	void OutPutPeInfo(CString &m_PeInfo, DWORD PeValue);	//输出PE相关信息
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton11();
};

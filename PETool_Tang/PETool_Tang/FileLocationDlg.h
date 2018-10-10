#pragma once


// FileLocationDlg 对话框

class FileLocationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FileLocationDlg)

public:
	FileLocationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FileLocationDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = FileLocation };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void  LockEdit(int EditId);					//锁定指定编辑框

	afx_msg void OnBnClickedButton1();//选择VA
	afx_msg void OnBnClickedButton2();//选择rva
	afx_msg void OnBnClickedButton3();//选择FOA
	afx_msg void OnEnChangeEdit1();//改变文本框
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	CString m_Va;
	CString m_Rva;
	CString m_Offset;
	CString m_Section;//区段
	CString m_Byte;//字节

	CString m_StrPDosAddr;


	DWORD ExclusiveCalcOffset(DWORD Rva);

	DWORD FoaToRva(DWORD dwFoa);//文件地址转虚拟内存地址

	afx_msg void OnBnClickedButton4();//计算
};

#pragma once
#include "CMyList.h"


// CPETLS 对话框

class TLSTableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TLSTableDlg)

public:
	TLSTableDlg(PIMAGE_DOS_HEADER pDos, PIMAGE_NT_HEADERS32 pNTHeader, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TLSTableDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = TLSTable };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	PIMAGE_DOS_HEADER m_pDos;		   //DOS头
	PIMAGE_NT_HEADERS32 m_pNTHeader;   //NT头
	PIMAGE_DATA_DIRECTORY m_pDataDir;  //目录头
	CString m_FunAdd;				   //函数地址

	CMyList m_ListTLS;				   //TLS列表

	CString m_StartAddressOfRawData;//起始地址
	CString m_EndAddressOfRawData;//结束地址
	CString m_AddressOfIndex;//索引
	CString m_AddressOfCallBacks;//回调函数
	CString m_SizeOfZeroFill;//填充0数量
	CString m_Characteristics;//属性


	void GetTLSInfo();				   //获取TLS信息
	DWORD RVA2FO(DWORD dwRva, PIMAGE_NT_HEADERS32 pNt);//rva转foa
};

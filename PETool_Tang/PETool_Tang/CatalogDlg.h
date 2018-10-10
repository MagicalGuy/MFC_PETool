#pragma once


// CatalogDlg 对话框

class CatalogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CatalogDlg)

public:
	CatalogDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CatalogDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = Catalog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	void ShowPeInfo();
	void OutPutPeInfo(CString &m_PeRvaInfo, CString &m_PeSizeInfo, DWORD PeRvaValue, DWORD PeSizeValue);//输出PE相关信息

	CString m_ExportRva;//输出表
	CString m_ExportSize;
	CString m_ImportRva;//输入表
	CString m_ImportSize;
	CString m_ResourceRva;//资源表
	CString m_ResourceSize;
	CString m_ExceptionRva;//例外
	CString m_ExceptionSize;
	CString m_SecurityRva;//安全
	CString m_SecuritySize;
	CString m_BaserelocRva;//重定位
	CString m_BaserelocSize;
	CString M_DebugRva;//调试
	CString M_DebugSize;
	CString m_ArchitectureRva;//版权
	CString m_ArchitectureSize;
	CString m_GlobalptrRva;//全局指针
	CString m_GlobalptrSize;
	CString m_TlsRva;//TLS
	CString m_TlsSize;
	CString m_LoadConfigRva;//载入配置
	CString m_LoadConfigSize;
	CString m_BoundImportRva;//输入范围
	CString m_BoundImportSize;
	CString m_IatRva;//IAT
	CString m_IatSize;
	CString m_DelayImportRva;//延迟加载表
	CString m_DelayImportSize;
	CString m_ComDescriptorRva;//com
	CString m_ComDescriptorSize;
	afx_msg void OnBnClickedButton17();//输出表
	afx_msg void OnBnClickedButton18();//输入表
	afx_msg void OnBnClickedButton19();//资源表
	afx_msg void OnBnClickedButton20();//重定位
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton21();//局部线程存储
	afx_msg void OnBnClickedButton22();//延迟加载表
};

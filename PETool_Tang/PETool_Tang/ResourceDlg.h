#pragma once
#include "afxcmn.h"


// ResourceDlg �Ի���

class ResourceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ResourceDlg)

public:
	ResourceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ResourceDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = Resource };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DWORD RVAToOffset(IMAGE_DOS_HEADER* pDos, DWORD dwRva);
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_ResourceTree;//���ؼ�


	DWORD m_dwResRootRva;//��Դ��Ŀ¼RVA
	IMAGE_RESOURCE_DIRECTORY* m_pResRoot;//��ԴĿ¼

	void parseResourcesTable(DWORD dwResRootDirAddr,/*��Ŀ¼���׵�ַ*/
		IMAGE_RESOURCE_DIRECTORY* pResDir,/*��Ҫ��������ԴĿ¼*/
		int nDeep /*��¼���ǵڼ���Ŀ¼*/
	);
	IMAGE_DOS_HEADER* m_pDosHdr;
	HTREEITEM hTree1 = NULL;
	HTREEITEM hTree2 = NULL;
	virtual BOOL OnInitDialog();
};

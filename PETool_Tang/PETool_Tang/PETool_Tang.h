
// PETool_Tang.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPETool_TangApp: 
// �йش����ʵ�֣������ PETool_Tang.cpp
//

class CPETool_TangApp : public CWinApp
{
public:
	CPETool_TangApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPETool_TangApp theApp;
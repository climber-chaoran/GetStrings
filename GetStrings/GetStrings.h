
// GetStrings.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGetStringsApp:
// �йش����ʵ�֣������ GetStrings.cpp
//

class CGetStringsApp : public CWinAppEx
{
public:
	CGetStringsApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGetStringsApp theApp;
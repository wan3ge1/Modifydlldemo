
// GenerateDllToy.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGenerateDllToyApp: 
// �йش����ʵ�֣������ GenerateDllToy.cpp
//

class CGenerateDllToyApp : public CWinApp
{
public:
	CGenerateDllToyApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGenerateDllToyApp theApp;

// Bilibili.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBilibiliApp: 
// �йش����ʵ�֣������ Bilibili.cpp
//

class CBilibiliApp : public CWinApp
{
public:
	CBilibiliApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBilibiliApp theApp;
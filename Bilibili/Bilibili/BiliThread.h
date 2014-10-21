#pragma once

#include "BiliThreadRun.h"
#include "BiliLogin.h"
#include "BiliReg.h"

// BiliThread

class BiliThread : public CWinThread
{
	DECLARE_DYNCREATE(BiliThread)

protected:
	BiliThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~BiliThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLogin(WPARAM wParam, LPARAM lParam);
	afx_msg void OnReg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnGetvdcode(WPARAM wParam, LPARAM lParam);
};



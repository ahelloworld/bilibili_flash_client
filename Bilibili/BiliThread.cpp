// BiliThread.cpp : 实现文件
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliThread.h"


// BiliThread

IMPLEMENT_DYNCREATE(BiliThread, CWinThread)

BiliThread::BiliThread()
{
}

BiliThread::~BiliThread()
{
}

BOOL BiliThread::InitInstance()
{
	// TODO:    在此执行任意逐线程初始化
	return TRUE;
}

int BiliThread::ExitInstance()
{
	// TODO:    在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(BiliThread, CWinThread)
	ON_THREAD_MESSAGE(WM_THLOGIN, OnLogin)
	ON_THREAD_MESSAGE(WM_THREG, OnReg)
	ON_THREAD_MESSAGE(WM_THVDCODE, OnGetvdcode)
END_MESSAGE_MAP()


// BiliThread 消息处理程序

void BiliThread::OnLogin(WPARAM wParam, LPARAM lParam)
{
	BiliLogin* loginbox = (BiliLogin*)wParam;
	BiliThreadRun* dlg = (BiliThreadRun*)lParam;
	ATL::CAtlString Email = (ATL::CAtlString)loginbox->EMAIL;
	ATL::CAtlString Pwd = (ATL::CAtlString)loginbox->PWD;

	Sleep(1000);
	CString str = L"正在登录中";
	dlg->SendMessage(WM_SETSTATE, (WPARAM)&str, 0);
	dlg->SendMessage(WM_SETPROGRESS, 25, 0);

	if (!UpdateCookie(Email, Pwd))
	{
		CString str = L"无法登录,请检测账号是否禁封或失效!";
		dlg->SendMessage(WM_SETSTATE, (WPARAM)&str, 0);
		dlg->SendMessage(WM_SETPROGRESS, 100, 0);
		dlg->PostMessage(WM_COMMAND, IDCANCEL, 0);
		return;
	}
	else
	{
		//		MessageBox(L"成功登录!");
		str = L"成功登录!";
		dlg->SendMessage(WM_SETSTATE, (WPARAM)&str, 0);
		dlg->SendMessage(WM_SETPROGRESS, 50, 0);
	}
	str = L"准备获取个人信息";
	dlg->SendMessage(WM_SETSTATE, (WPARAM)&str, 0);
	dlg->SendMessage(WM_SETPROGRESS, 75, 0);
	if (!Myinfo(Email, loginbox->mid, loginbox->rank, loginbox->coins, loginbox->sex, loginbox->hBmp, loginbox->name))
	{
		if (loginbox->mid != 0)
		{
			CString code;
			code.Format(L"错误代码:%d", loginbox->mid);
			dlg->SendMessage(WM_SETSTATE, (WPARAM)&code, 0);
			dlg->SendMessage(WM_SETPROGRESS, 50, 0);
			dlg->SendMessage(WM_SETSTATE, (WPARAM)&loginbox->name, 0);
			dlg->SendMessage(WM_SETPROGRESS, 100, 0);
		}
		dlg->PostMessage(WM_COMMAND, IDCANCEL, 0);
		return;
	}
	else
	{
		str = L"成功获取个人信息!";
		dlg->SendMessage(WM_SETSTATE, (WPARAM)&str, 0);
		dlg->SendMessage(WM_SETPROGRESS, 100, 0);
	}
	dlg->PostMessage(WM_COMMAND, IDOK, 0);
}

void BiliThread::OnGetvdcode(WPARAM wParam, LPARAM lParam)
{
	BiliReg* loginbox = (BiliReg*)wParam;
	BiliThreadRun* dlg = (BiliThreadRun*)lParam;
	Sleep(1000);
	CString str = L"正在获取验证码";
	dlg->SendMessage(WM_SETSTATE, (WPARAM)&str, 0);
	dlg->SendMessage(WM_SETPROGRESS, 100, 0);
	if (!GetVdcode(loginbox->hBmp))
	{
		CString str = L"无法获取验证码,请检测网络";
		dlg->SendMessage(WM_SETSTATE, (WPARAM)&str, 0);
		dlg->SendMessage(WM_SETPROGRESS, 100, 0);
		loginbox->flag = FALSE;
		dlg->PostMessage(WM_COMMAND, IDCANCEL, 0);
	}
	else
	{
		CString str = L"成功获取验证码";
		dlg->SendMessage(WM_SETSTATE, (WPARAM)&str, 0);
		dlg->SendMessage(WM_SETPROGRESS, 100, 0);
		loginbox->flag = TRUE;
		dlg->PostMessage(WM_COMMAND, IDOK, 0);
	}
}

void BiliThread::OnReg(WPARAM wParam, LPARAM lParam)
{
	BiliReg* loginbox = (BiliReg*)wParam;
	BiliThreadRun* dlg = (BiliThreadRun*)lParam;
	Sleep(1000);
	CString str = L"正在注册中...";
	dlg->SendMessage(WM_SETSTATE, (WPARAM)&str, 0);
	dlg->SendMessage(WM_SETPROGRESS, 50, 0);
	ATL::CAtlString res;
	if (Reg((ATL::CAtlString)loginbox->Email, (ATL::CAtlString)loginbox->Uname, (ATL::CAtlString)loginbox->Pwd, (ATL::CAtlString)loginbox->Vdcode, res))
	{
		dlg->SendMessage(WM_SETSTATE, (WPARAM)&(CString)res, 0);
		dlg->SendMessage(WM_SETPROGRESS, 50, 0);
		return;
	}
	str = L"注册成功,正在准备登录...";
	Sleep(2000);
	dlg->SendMessage(WM_SETSTATE, (WPARAM)&str, 0);
	dlg->SendMessage(WM_SETPROGRESS, 50, 0);
}
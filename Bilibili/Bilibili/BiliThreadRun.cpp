// BiliThreadRun.cpp : 实现文件
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliThreadRun.h"
#include "afxdialogex.h"


// BiliThreadRun 对话框

IMPLEMENT_DYNAMIC(BiliThreadRun, CDialogEx)

BiliThreadRun::BiliThreadRun(CWnd* pParent /*=NULL*/)
	: CDialogEx(BiliThreadRun::IDD, pParent)
	, state(_T(""))
{

}

BiliThreadRun::~BiliThreadRun()
{
}

void BiliThreadRun::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_THREADRUN, m_crtlProgress);
	DDX_Text(pDX, IDC_THREADSTATE, state);
}


BEGIN_MESSAGE_MAP(BiliThreadRun, CDialogEx)
	ON_MESSAGE(WM_SETSIZE, OnSetSize)
	ON_MESSAGE(WM_SETSTATE, OnSetState)
	ON_MESSAGE(WM_SETPROGRESS, OnSetProgress)
END_MESSAGE_MAP()


// BiliThreadRun 消息处理程序

LRESULT BiliThreadRun::OnSetSize(WPARAM wParam, LPARAM lParam)
{
	size = (int)wParam;
	return 0;
}

LRESULT BiliThreadRun::OnSetState(WPARAM wParam, LPARAM lParam)
{
	state = *(CString*)wParam;
	((CString*)wParam)->ReleaseBuffer();
	UpdateData(FALSE);
	return 0;
}

LRESULT BiliThreadRun::OnSetProgress(WPARAM wParam, LPARAM lParam)
{
	m_crtlProgress.SetPos((int)wParam);
	return 0;
}


BOOL BiliThreadRun::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ModifyStyleEx(0, WS_EX_LAYERED /*| WS_EX_TRANSPARENT*/);
	SetLayeredWindowAttributes(RGB(250, 250, 250), 180, LWA_ALPHA | LWA_COLORKEY);
	SetBackgroundColor(RGB(250, 250, 250));
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void BiliThreadRun::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void BiliThreadRun::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}

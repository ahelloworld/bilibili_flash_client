// BiliLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliLogin.h"
#include "afxdialogex.h"


// BiliLogin 对话框

IMPLEMENT_DYNAMIC(BiliLogin, CDialogEx)

BiliLogin::BiliLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(BiliLogin::IDD, pParent)
	, EMAIL(_T(""))
	, PWD(_T(""))
{

}

BiliLogin::~BiliLogin()
{
}

void BiliLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INEMAIL, EMAIL);
	DDX_Text(pDX, IDC_INPWD, PWD);
}


BEGIN_MESSAGE_MAP(BiliLogin, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDOK, &BiliLogin::OnBnClickedOk)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// BiliLogin 消息处理程序


BOOL BiliLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ModifyStyleEx(0, WS_EX_LAYERED /*| WS_EX_TRANSPARENT*/);
	SetLayeredWindowAttributes(0, 190, LWA_ALPHA);
	SetBackgroundColor(RGB(230, 250, 250));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void BiliLogin::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


void BiliLogin::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	CDialogEx::OnOK();
	DestroyWindow();
}


void BiliLogin::Login()
{
	int found = EMAIL.Find(L"@");
	if (found == -1 || EMAIL.Find(L".", found) == -1 || EMAIL.Find(L".", found) == (EMAIL.GetLength() - 1))
	{
		MessageBox(L"输入的邮箱账号不对,请重新输入");
		return;
	}
	BiliThreadRun dlg;
	m_pThrd->PostThreadMessageW(WM_THLOGIN, (WPARAM)this, (LPARAM)&dlg);
	INT_PTR pr = dlg.DoModal();
	if (pr == IDCANCEL)
	{
		MessageBox(L"登录失败");
	}
	else if (pr == IDOK)
	{
		GetParent()->SendMessage(WM_LOGINOK, 0, 0);
	}
	CDialogEx::OnOK();
}


void BiliLogin::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Login();
	CDialogEx::OnOK();
}


void BiliLogin::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliLogin::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO:  在此处添加消息处理程序代码
//	delete this;
}


void BiliLogin::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();
	delete this;
}

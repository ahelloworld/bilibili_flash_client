// BiliPlayer.cpp : 实现文件
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliPlayer.h"
#include "afxdialogex.h"


// BiliPlayer 对话框

IMPLEMENT_DYNAMIC(BiliPlayer, CDialogEx)

BiliPlayer::BiliPlayer(CWnd* pParent /*=NULL*/)
	: CDialogEx(BiliPlayer::IDD, pParent)
{

}

BiliPlayer::~BiliPlayer()
{
}

void BiliPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, player);
}


BEGIN_MESSAGE_MAP(BiliPlayer, CDialogEx)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// BiliPlayer 消息处理程序


BOOL BiliPlayer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void BiliPlayer::Player(CString &url)
{
	player.Navigate(url, NULL, NULL, NULL, NULL);
}


BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lparam)
{
	wchar_t name[1000];
	GetClassName(hwnd, name, 1024);
	if (!wcscmp(name, L"MacromediaFlashPlayerActiveX"/*L"Internet Explorer_Server"*/))
	{
		InvalidateRect(hwnd, NULL, TRUE);
//		SendMessage(hwnd, WM_NCPAINT, 1, 0);

	}
	return TRUE;
}

void BiliPlayer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	EnumChildWindows(m_hWnd, EnumChildWindowsProc, -1);
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void BiliPlayer::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
	DestroyWindow();
}


void BiliPlayer::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliPlayer::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
//	delete this;
}


void BiliPlayer::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();
	delete this;
}

// BiliMenu.cpp : 实现文件
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliMenu.h"
#include "afxdialogex.h"


// BiliMenu 对话框

IMPLEMENT_DYNAMIC(BiliMenu, CDialogEx)

BiliMenu::BiliMenu(CWnd* pParent /*=NULL*/)
	: CDialogEx(BiliMenu::IDD, pParent)
{

}

BiliMenu::~BiliMenu()
{
}

void BiliMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BiliMenu, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// BiliMenu 消息处理程序


BOOL BiliMenu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	line = -1;

	ModifyStyleEx(0, WS_EX_LAYERED /*| WS_EX_TRANSPARENT*/);
	SetLayeredWindowAttributes(0, 150, LWA_ALPHA);

	menu[0] = L"注册账号";
	menu[1] = L"设置背景";
	menu[2] = L"登录账号";
	menu[3] = L"刷新所有";
	menu[4] = L"打开视频";
	menu[5] = L"帮助文档";
	menu[6] = L"关于程序";
	menu[7] = L"退出程序";
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void BiliMenu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(BackgroundBitmap);
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);

	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void BiliMenu::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int w = rc.Width();
	int h = rc.Height();
	int i;
	for (i = menu_num; i >= 1; i--)
	{
		int lineH = (i - 1)*h / menu_num;
		if (point.y > lineH)
		{
			if (line != i)
			{
				InvalidateRect(NULL, FALSE);
				UpdateWindow();
				CDC *pDC = GetDC();
				Gdiplus::Graphics g(*pDC);
				Gdiplus::Pen pen(Gdiplus::Color(0, 255, 255), 2);
				g.DrawRectangle(&pen, 0, lineH, w, h / menu_num);
				line = i;
			}
			break;
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void BiliMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int w = rc.Width();
	int h = rc.Height();
	int i;
	for (i = menu_num; i >= 1; i--)
	{
		int lineH = (i - 1)*h / menu_num;
		if (point.y > lineH)
		{
			if (line != i)
			{
				CDC *pDC = GetDC();
				Gdiplus::Graphics g(*pDC);
				Gdiplus::Pen pen(Gdiplus::Color(0, 255, 255), 2);
				g.DrawRectangle(&pen, 0, lineH, w, h / menu_num);
				line = i;
			}
			break;
		}
	}
	GetParent()->SendMessage(WM_LBUTTONDOWN, HTCAPTION, MAKELPARAM(0, 0));
	switch (i)
	{
	case 1:
		GetParent()->PostMessageW(WM_REG, 0, 0);
		break;
	case 2:
		GetParent()->PostMessageW(WM_SETBG, 0, 0);
		break;
	case 3:
		GetParent()->PostMessageW(WM_LOGIN, 0, 0);
		break;
	case 4:
		MessageBox(menu[3]);
		break;
	case 5:
		GetParent()->PostMessageW(WM_OPENVIDEO, 0, 0);
		break;
	case 6:
		MessageBox(L"暂时木有,就是凑数的");
		break;
	case 7:
		MessageBox(L"bilibili账户管理系统 v1.0\r\n制作by:xxx\r\n使用开源库:\r\n\tcurl库\r\n\tjson库\r\n\t等等...\r\n22和33娘图片来源:\r\n\tbilibili官网壁纸@深渊");
		break;
	case 8:
		GetParent()->PostMessage(WM_COMMAND, IDOK, 0);
		break;
	default:
		break;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void BiliMenu::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonUp(nFlags, point);
}


void BiliMenu::BackgroundSave()
{
	CPaintDC dc(this);
	int w = rc.Width();
	int h = rc.Height();

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, w, h);
	memDC.SelectObject(&bmp);

	Gdiplus::Graphics memGr(memDC.m_hDC);

	Gdiplus::SolidBrush bgcolor(Gdiplus::Color(247, 245, 235));// 菜单背景色

	memGr.FillRectangle(&bgcolor, 0, 0, rc.Width(), rc.Height());

	Gdiplus::Pen pen(Gdiplus::Color(195, 175, 165), 2);
	Gdiplus::SolidBrush brush(Gdiplus::Color(0, 0, 0));

	Gdiplus::FontFamily fontFamily(L"微软雅黑");
	Gdiplus::Font font(&fontFamily, 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

	int i = 0;
	for (i = 1; i < menu_num; i++)
	{
		int lineH = i*h / menu_num;
		Gdiplus::PointF pointF(7, lineH - 30);
		memGr.DrawString(menu[i - 1], -1, &font, pointF, &brush);
		memGr.DrawLine(&pen, 0, lineH, w, lineH);
	}
	Gdiplus::PointF pointF(7, h - 30);
	memGr.DrawString(menu[i - 1], -1, &font, pointF, &brush);

	BackgroundBitmap = (HBITMAP*)bmp.Detach();
	memDC.DeleteDC();
	bmp.DeleteObject();
	InvalidateRect(NULL, FALSE);
}


void BiliMenu::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	// TODO:  在此处添加消息处理程序代码
	GetClientRect(rc);
	BackgroundSave();
}


void BiliMenu::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO:  在此处添加消息处理程序代码
	switch (nState)
	{
	case WA_INACTIVE:
		line = -1;
		break;
	
	//case WA_ACTIVE:
	//	MessageBox(L"active");
	//	break;

	//case WA_CLICKACTIVE:
	//	MessageBox(L"click");
	//	break;
	
	default:
		break;
	}
}


void BiliMenu::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
	DestroyWindow();
}


void BiliMenu::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliMenu::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
//	delete this;
}


void BiliMenu::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();
	delete this;
}

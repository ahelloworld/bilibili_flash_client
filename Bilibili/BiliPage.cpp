// BiliPage.cpp : 实现文件
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliPage.h"
#include "afxdialogex.h"


// BiliPage 对话框

IMPLEMENT_DYNAMIC(BiliPage, CDialogEx)

BiliPage::BiliPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(BiliPage::IDD, pParent)
{

}

BiliPage::~BiliPage()
{
}

void BiliPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BiliPage, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// BiliPage 消息处理程序


void BiliPage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(BackgroundBitmap);

	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);
	
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


BOOL BiliPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pages = 1;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void BiliPage::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (point.y < rc.bottom && point.y > rc.top)
	{
		if (point.x > rc.left)
		{
			int pageW;
			if (pages <= 3)
			{
				pageW = rc.Width() / 4;
			}
			else
			{
				pageW = rc.Width() / pages + 1;
			}
			int i;
			for (i = 1; i <= pages; i++)
			{
				if (point.x < i * pageW)
				{
					MessageBox(L"击中标签栏");
					break;
				}
			}
			if (i > pages)
			{
				if (point.x < pages * pageW + rc.Width() / 20)
				{
					MessageBox(L"击中增加标签");
				}
				else
				{
					GetParent()->SendMessage(WM_LBUTTONDOWN, HTCAPTION, MAKELPARAM(0, 0));
//					GetParent()->SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
				}
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void BiliPage::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	GetClientRect(rc);
	// TODO:  在此处添加消息处理程序代码
}


void BiliPage::BackgroundSave(int r_, int g_, int b_)
{
	CPaintDC dc(this); 

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	memDC.SelectObject(bmp);

	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	POINT pt_wnd = { rc.left, rc.top }, pt_mem = { 0, 0 };
	SIZE sz_wnd = { rc.Width(), rc.Height() };

	Gdiplus::Graphics memGr(memDC.m_hDC);
	Gdiplus::Pen newPen(Gdiplus::Color(130, 135, 144), 0);
	Gdiplus::SolidBrush newBrush(Gdiplus::Color(255, 255, 255));
	Gdiplus::SolidBrush new2Brush(Gdiplus::Color(210, 210, 210));
	Gdiplus::SolidBrush fontBrush(Gdiplus::Color(0, 0, 0));

	Gdiplus::SolidBrush background(Gdiplus::Color(r_, g_, b_));

	Gdiplus::FontFamily fontFamily(L"微软雅黑");
	int pageW;
	int pages = 1;
	int width = rc.Width();
	int height = rc.Height();
	if (pages <= 3)
	{
		pageW = width / 4;
	}
	else
	{
		pageW = width / pages + 1;
	}

	Gdiplus::Font font(&fontFamily, 15, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::PointF pointF(5, 5);

	//memGr.SetTextRenderingHint(Gdiplus::TextRenderingHintSystemDefault);
	//memGr.SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);
	//memGr.SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixel);
	//memGr.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);
	//memGr.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	//memGr.SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);

	int temp = 0;
	for (int i = 0; i < pages; i++)
	{
		memGr.FillRectangle(&newBrush, temp, 0, temp + pageW, height);
		memGr.DrawRectangle(&newPen, temp, 0, temp + pageW, height);
		memGr.DrawString(L"BiliBili", -1, &font, pointF, &fontBrush);
		temp += pageW;
	}
	memGr.FillRectangle(&new2Brush, temp, 0, width / 20, height);
	memGr.DrawRectangle(&newPen, temp, 0, width / 20, height);

	memGr.FillRectangle(&background, temp + width / 20 + 1, 0, width, height);

	BackgroundBitmap = (HBITMAP*)bmp.Detach();
	memDC.DeleteDC();
	bmp.DeleteObject();
	InvalidateRect(NULL, FALSE);
}


void BiliPage::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	CDialogEx::OnOK();
	DestroyWindow();
}


void BiliPage::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliPage::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO:  在此处添加消息处理程序代码
//	delete this;
}


void BiliPage::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();
	delete this;
}

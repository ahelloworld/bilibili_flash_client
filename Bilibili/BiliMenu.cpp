// BiliMenu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliMenu.h"
#include "afxdialogex.h"


// BiliMenu �Ի���

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


// BiliMenu ��Ϣ�������


BOOL BiliMenu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	line = -1;

	ModifyStyleEx(0, WS_EX_LAYERED /*| WS_EX_TRANSPARENT*/);
	SetLayeredWindowAttributes(0, 150, LWA_ALPHA);

	menu[0] = L"ע���˺�";
	menu[1] = L"���ñ���";
	menu[2] = L"��¼�˺�";
	menu[3] = L"ˢ������";
	menu[4] = L"����Ƶ";
	menu[5] = L"�����ĵ�";
	menu[6] = L"���ڳ���";
	menu[7] = L"�˳�����";
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void BiliMenu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(BackgroundBitmap);
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void BiliMenu::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		MessageBox(L"��ʱľ��,���Ǵ�����");
		break;
	case 7:
		MessageBox(L"bilibili�˻�����ϵͳ v1.0\r\n����by:xxx\r\nʹ�ÿ�Դ��:\r\n\tcurl��\r\n\tjson��\r\n\t�ȵ�...\r\n22��33��ͼƬ��Դ:\r\n\tbilibili������ֽ@��Ԩ");
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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

	Gdiplus::SolidBrush bgcolor(Gdiplus::Color(247, 245, 235));// �˵�����ɫ

	memGr.FillRectangle(&bgcolor, 0, 0, rc.Width(), rc.Height());

	Gdiplus::Pen pen(Gdiplus::Color(195, 175, 165), 2);
	Gdiplus::SolidBrush brush(Gdiplus::Color(0, 0, 0));

	Gdiplus::FontFamily fontFamily(L"΢���ź�");
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
	
	// TODO:  �ڴ˴������Ϣ����������
	GetClientRect(rc);
	BackgroundSave();
}


void BiliMenu::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO:  �ڴ˴������Ϣ����������
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
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
	DestroyWindow();
}


void BiliMenu::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliMenu::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
//	delete this;
}


void BiliMenu::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::PostNcDestroy();
	delete this;
}

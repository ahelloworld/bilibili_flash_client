// BiliFace.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliFace.h"
#include "afxdialogex.h"


// BiliFace �Ի���

IMPLEMENT_DYNAMIC(BiliFace, CDialogEx)

BiliFace::BiliFace(CWnd* pParent /*=NULL*/)
	: CDialogEx(BiliFace::IDD, pParent)
{

}

BiliFace::~BiliFace()
{
}

void BiliFace::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FACE, m_face);
}


BEGIN_MESSAGE_MAP(BiliFace, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// BiliFace ��Ϣ�������


BOOL BiliFace::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetBackgroundColor(RGB(250, 250, 250));

	CImage img;
	img.Load(L"face.png");
	bmp = img.Detach();

	CString str1 = L"";
	CString str2 = L"";
	BackgroundSave(str1, str2);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void BiliFace::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(BackgroundBitmap);
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.DeleteDC();

	CDC* pDC = m_face.GetDC();
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(bmp);
	SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);
	CBitmap bitmap;
	bitmap.Attach(bmp);
	BITMAP bm;
	bitmap.GetBitmap(&bm);
	pDC->StretchBlt(0, 0, 130, 130, &memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	memDC.DeleteDC();
	bmp = (HBITMAP)bitmap.Detach();

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void BiliFace::BackgroundSave(CString &name,CString &coins)
{
	::DeleteObject(BackgroundBitmap);

	if (name == L"")
	{
		name = L"δ��¼";
	}
	if (coins == L"")
	{
		coins = L"δ��¼";
	}

	CPaintDC dc(this);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	memDC.SelectObject(&bmp);

	Gdiplus::Graphics memGr(memDC.m_hDC);

	Gdiplus::SolidBrush brush(Gdiplus::Color(0, 0, 0));

	Gdiplus::SolidBrush brush2(Gdiplus::Color(170, 180, 140));

	Gdiplus::SolidBrush colorkey(Gdiplus::Color(250, 250, 250));

	memGr.FillRectangle(&colorkey, 0, 0, rc.Width(), rc.Height());
	memGr.FillRectangle(&brush2, 135, 65, 120, 55);

	Gdiplus::FontFamily fontFamily(L"΢���ź�");
	Gdiplus::Font font(&fontFamily, 11, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

	Gdiplus::PointF pointF1(140, 70);
	memGr.DrawString(L"�ǳ�:" + name, -1, &font, pointF1, &brush);
	Gdiplus::PointF pointF2(140, 100);
	memGr.DrawString(L"Ӳ����:" + coins, -1, &font, pointF2, &brush);

	BackgroundBitmap = (HBITMAP*)bmp.Detach();
	memDC.DeleteDC();
	bmp.DeleteObject();
	InvalidateRect(NULL, TRUE);
}


void BiliFace::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	GetClientRect(&rc);
}


void BiliFace::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliFace::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
	DestroyWindow();
}


void BiliFace::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
//	delete this;
}


void BiliFace::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::PostNcDestroy();
	delete this;
}

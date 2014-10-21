// BiliBGSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliBGSet.h"
#include "afxdialogex.h"


// BiliBGSet 对话框

IMPLEMENT_DYNAMIC(BiliBGSet, CDialogEx)

BiliBGSet::BiliBGSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(BiliBGSet::IDD, pParent)
	, R_POS(0)
	, G_POS(0)
	, B_POS(0)
	, A_POS(0)
{

}

BiliBGSet::~BiliBGSet()
{
}

void BiliBGSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_R, R_POS);
	DDV_MinMaxInt(pDX, R_POS, 0, 255);
	DDX_Slider(pDX, IDC_G, G_POS);
	DDV_MinMaxInt(pDX, G_POS, 0, 255);
	DDX_Slider(pDX, IDC_B, B_POS);
	DDV_MinMaxInt(pDX, B_POS, 0, 255);
	DDX_Slider(pDX, IDC_A, A_POS);
	DDV_MinMaxInt(pDX, A_POS, 0, 255);
	DDX_Control(pDX, IDC_R, SETR);
	DDX_Control(pDX, IDC_G, SETG);
	DDX_Control(pDX, IDC_B, SETB);
	DDX_Control(pDX, IDC_A, SETA);
}


BEGIN_MESSAGE_MAP(BiliBGSet, CDialogEx)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_R, &BiliBGSet::OnNMReleasedcaptureR)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_G, &BiliBGSet::OnNMReleasedcaptureG)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_B, &BiliBGSet::OnNMReleasedcaptureB)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_A, &BiliBGSet::OnNMReleasedcaptureA)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_22, &BiliBGSet::OnBnClicked22)
	ON_BN_CLICKED(IDC_33, &BiliBGSet::OnBnClicked33)
END_MESSAGE_MAP()


// BiliBGSet 消息处理程序


BOOL BiliBGSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SETR.SetRange(0, 255);
	SETG.SetRange(0, 255);
	SETB.SetRange(0, 255);
	SETA.SetRange(0, 255);
	R_POS = r;
	G_POS = g;
	B_POS = b;
	A_POS = a;
	UpdateData(FALSE);

	((CButton*)GetDlgItem(IDC_22))->SetCheck(person);
	((CButton*)GetDlgItem(IDC_33))->SetCheck(!person);

	CRect rc;
	GetClientRect(rc);

	SetWindowPos(NULL, x, y - rc.Height(), 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}




void BiliBGSet::OnNMReleasedcaptureR(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD data = MAKEWPARAM(MAKEWORD(R_POS, G_POS), MAKEWORD(B_POS, 0/*A_POS*/));
	GetParent()->SendMessage(WM_CHANGEBG, data, 0);
	*pResult = 0;
}


void BiliBGSet::OnNMReleasedcaptureG(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD data = MAKEWPARAM(MAKEWORD(R_POS, G_POS), MAKEWORD(B_POS, 0/*A_POS*/));
	GetParent()->SendMessage(WM_CHANGEBG, data, 0);
	*pResult = 0;
}


void BiliBGSet::OnNMReleasedcaptureB(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD data = MAKEWPARAM(MAKEWORD(R_POS, G_POS), MAKEWORD(B_POS, 0/*A_POS*/));
	GetParent()->SendMessage(WM_CHANGEBG, data, 0);
	*pResult = 0;
}


void BiliBGSet::OnNMReleasedcaptureA(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GetParent()->SendMessage(WM_CHANGEBG, A_POS, 2);
	*pResult = 0;
}


void BiliBGSet::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


void BiliBGSet::OnBnClicked22()
{
	// TODO:  在此添加控件通知处理程序代码
	GetParent()->SendMessage(WM_CHANGEBG, 1, 1);
}



void BiliBGSet::OnBnClicked33()
{
	// TODO:  在此添加控件通知处理程序代码
	GetParent()->SendMessage(WM_CHANGEBG, 0, 1);
}

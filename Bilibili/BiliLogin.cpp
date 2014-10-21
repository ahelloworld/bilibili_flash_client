// BiliLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliLogin.h"
#include "afxdialogex.h"


// BiliLogin �Ի���

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


// BiliLogin ��Ϣ�������


BOOL BiliLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ModifyStyleEx(0, WS_EX_LAYERED /*| WS_EX_TRANSPARENT*/);
	SetLayeredWindowAttributes(0, 190, LWA_ALPHA);
	SetBackgroundColor(RGB(230, 250, 250));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void BiliLogin::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


void BiliLogin::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
	DestroyWindow();
}


void BiliLogin::Login()
{
	int found = EMAIL.Find(L"@");
	if (found == -1 || EMAIL.Find(L".", found) == -1 || EMAIL.Find(L".", found) == (EMAIL.GetLength() - 1))
	{
		MessageBox(L"����������˺Ų���,����������");
		return;
	}
	BiliThreadRun dlg;
	m_pThrd->PostThreadMessageW(WM_THLOGIN, (WPARAM)this, (LPARAM)&dlg);
	INT_PTR pr = dlg.DoModal();
	if (pr == IDCANCEL)
	{
		MessageBox(L"��¼ʧ��");
	}
	else if (pr == IDOK)
	{
		GetParent()->SendMessage(WM_LOGINOK, 0, 0);
	}
	CDialogEx::OnOK();
}


void BiliLogin::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	Login();
	CDialogEx::OnOK();
}


void BiliLogin::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliLogin::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO:  �ڴ˴������Ϣ����������
//	delete this;
}


void BiliLogin::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::PostNcDestroy();
	delete this;
}

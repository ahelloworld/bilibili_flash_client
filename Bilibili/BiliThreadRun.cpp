// BiliThreadRun.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliThreadRun.h"
#include "afxdialogex.h"


// BiliThreadRun �Ի���

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


// BiliThreadRun ��Ϣ�������

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ModifyStyleEx(0, WS_EX_LAYERED /*| WS_EX_TRANSPARENT*/);
	SetLayeredWindowAttributes(RGB(250, 250, 250), 180, LWA_ALPHA | LWA_COLORKEY);
	SetBackgroundColor(RGB(250, 250, 250));
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void BiliThreadRun::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void BiliThreadRun::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}

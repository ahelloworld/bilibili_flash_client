// BiliPlayer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliPlayer.h"
#include "afxdialogex.h"


// BiliPlayer �Ի���

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


// BiliPlayer ��Ϣ�������


BOOL BiliPlayer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
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
	// TODO:  �ڴ˴������Ϣ����������
	EnumChildWindows(m_hWnd, EnumChildWindowsProc, -1);
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void BiliPlayer::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
	DestroyWindow();
}


void BiliPlayer::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliPlayer::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
//	delete this;
}


void BiliPlayer::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::PostNcDestroy();
	delete this;
}

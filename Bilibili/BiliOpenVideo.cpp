// BiliOpenVideo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliOpenVideo.h"
#include "afxdialogex.h"


// BiliOpenVideo �Ի���

IMPLEMENT_DYNAMIC(BiliOpenVideo, CDialogEx)

BiliOpenVideo::BiliOpenVideo(CWnd* pParent /*=NULL*/)
	: CDialogEx(BiliOpenVideo::IDD, pParent)
	, avnum(_T(""))
{

}

BiliOpenVideo::~BiliOpenVideo()
{
}

void BiliOpenVideo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AVGET, avnum);
}


BEGIN_MESSAGE_MAP(BiliOpenVideo, CDialogEx)
END_MESSAGE_MAP()


// BiliOpenVideo ��Ϣ�������


void BiliOpenVideo::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	CDialogEx::OnOK();
}

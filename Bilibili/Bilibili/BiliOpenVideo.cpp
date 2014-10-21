// BiliOpenVideo.cpp : 实现文件
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliOpenVideo.h"
#include "afxdialogex.h"


// BiliOpenVideo 对话框

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


// BiliOpenVideo 消息处理程序


void BiliOpenVideo::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData(TRUE);
	CDialogEx::OnOK();
}

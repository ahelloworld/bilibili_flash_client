// BiliList.cpp : 实现文件
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliList.h"
#include "afxdialogex.h"


// BiliList 对话框

IMPLEMENT_DYNAMIC(BiliList, CDialogEx)

BiliList::BiliList(CWnd* pParent /*=NULL*/)
	: CDialogEx(BiliList::IDD, pParent)
{

}

BiliList::~BiliList()
{
}

void BiliList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}


BEGIN_MESSAGE_MAP(BiliList, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST, &BiliList::OnNMClickList)
END_MESSAGE_MAP()


// BiliList 消息处理程序


BOOL BiliList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc;
	GetClientRect(&rc);

	m_list.InsertColumn(0, L"视频名称", LVCFMT_LEFT, 136);
	m_list.InsertColumn(1, L"cid", LVCFMT_LEFT, 80);
	m_list.InsertColumn(2, L"点击量", LVCFMT_LEFT, 80);
	m_list.InsertColumn(3, L"播放量", LVCFMT_LEFT, 83);
	m_list.InsertColumn(4, L"弹幕数", LVCFMT_LEFT, 63);
	m_list.InsertColumn(5, L"收藏数", LVCFMT_LEFT, 60);
	m_list.InsertColumn(6, L"其他信息", LVCFMT_LEFT, rc.Width() - 508);
	m_list.SetExtendedStyle(
		//		| LVS_EX_FLATSB							//扁平风格滚动条
		//		| LVS_EX_FULLROWSELECT					//允许整行选中
		//		| LVS_EX_HEADERDRAGDROP					//允许标题拖曳
		//		| LVS_EX_ONECLICKACTIVATE				//高亮显示
		LVS_EX_GRIDLINES);						//画出网格线
	CHeaderCtrl* pHeaderCtrl = (CHeaderCtrl*)m_list.GetHeaderCtrl();//关闭修改listbox头
	pHeaderCtrl->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void BiliList::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnClose();
}


void BiliList::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	CDialogEx::OnOK();
	DestroyWindow();
}


void BiliList::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliList::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO:  在此处添加消息处理程序代码
//	delete this;
}


void BiliList::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	GetParent()->SendMessage(WM_LBUTTONDOWN, HTCAPTION, MAKELPARAM(0, 0));
	*pResult = 0;
}


void BiliList::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();
	delete this;
}

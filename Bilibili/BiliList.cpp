// BiliList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliList.h"
#include "afxdialogex.h"


// BiliList �Ի���

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


// BiliList ��Ϣ�������


BOOL BiliList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	GetClientRect(&rc);

	m_list.InsertColumn(0, L"��Ƶ����", LVCFMT_LEFT, 136);
	m_list.InsertColumn(1, L"cid", LVCFMT_LEFT, 80);
	m_list.InsertColumn(2, L"�����", LVCFMT_LEFT, 80);
	m_list.InsertColumn(3, L"������", LVCFMT_LEFT, 83);
	m_list.InsertColumn(4, L"��Ļ��", LVCFMT_LEFT, 63);
	m_list.InsertColumn(5, L"�ղ���", LVCFMT_LEFT, 60);
	m_list.InsertColumn(6, L"������Ϣ", LVCFMT_LEFT, rc.Width() - 508);
	m_list.SetExtendedStyle(
		//		| LVS_EX_FLATSB							//��ƽ��������
		//		| LVS_EX_FULLROWSELECT					//��������ѡ��
		//		| LVS_EX_HEADERDRAGDROP					//���������ҷ
		//		| LVS_EX_ONECLICKACTIVATE				//������ʾ
		LVS_EX_GRIDLINES);						//����������
	CHeaderCtrl* pHeaderCtrl = (CHeaderCtrl*)m_list.GetHeaderCtrl();//�ر��޸�listboxͷ
	pHeaderCtrl->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void BiliList::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnClose();
}


void BiliList::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
	DestroyWindow();
}


void BiliList::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliList::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO:  �ڴ˴������Ϣ����������
//	delete this;
}


void BiliList::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetParent()->SendMessage(WM_LBUTTONDOWN, HTCAPTION, MAKELPARAM(0, 0));
	*pResult = 0;
}


void BiliList::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::PostNcDestroy();
	delete this;
}

// BiliReg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliReg.h"
#include "afxdialogex.h"


// BiliReg �Ի���

IMPLEMENT_DYNAMIC(BiliReg, CDialogEx)

BiliReg::BiliReg(CWnd* pParent /*=NULL*/)
	: CDialogEx(BiliReg::IDD, pParent)
	, Email(_T(""))
	, Uname(_T(""))
	, Pwd(_T(""))
	, Vdcode(_T(""))
	, FILL(FALSE)
	, flag(FALSE)
{

}

BiliReg::~BiliReg()
{
}

void BiliReg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EMAIL, Email);
	DDX_Text(pDX, IDC_UNAME, Uname);
	DDX_Text(pDX, IDC_PWD, Pwd);
	DDX_Text(pDX, IDC_VDCODE, Vdcode);
	DDX_Check(pDX, IDC_FILL, FILL);
}


BEGIN_MESSAGE_MAP(BiliReg, CDialogEx)
	ON_BN_CLICKED(IDC_GETCHEMAIL, &BiliReg::OnBnClickedGetchemail)
	ON_BN_CLICKED(IDC_CHUNAME, &BiliReg::OnBnClickedChuname)
	ON_BN_CLICKED(IDC_CHPWD, &BiliReg::OnBnClickedChpwd)
	ON_BN_CLICKED(IDC_GETVDCODE, &BiliReg::OnBnClickedGetvdcode)
	ON_BN_CLICKED(IDC_REG, &BiliReg::OnBnClickedReg)
	ON_BN_CLICKED(IDOK, &BiliReg::OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_FILL, &BiliReg::OnBnClickedFill)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// BiliReg ��Ϣ�������


void BiliReg::OnBnClickedGetchemail()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	ATL::CAtlString res;
	Check((ATL::CAtlString)Email, 0, res);
	MessageBox(res);
}


void BiliReg::OnBnClickedChuname()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	ATL::CAtlString res;
	Check((ATL::CAtlString)Uname, 1, res);
	MessageBox(res);
}


void BiliReg::OnBnClickedChpwd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	ATL::CAtlString res;
	Check((ATL::CAtlString)Pwd, 2, res);
	MessageBox(res);
}


void BiliReg::OnBnClickedGetvdcode()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	::DeleteObject(hBmp);
	if (GetVdcode(hBmp))
	{
		CImage image;
		image.Attach(hBmp);
		image.Draw(GetDlgItem(IDC_VDCODESHOW)->GetDC()->m_hDC, CRect(0, 0, 110, 30));
		hBmp = image.Detach();
		flag = TRUE;
	}
	else
	{
		MessageBox(L"��ȡ��֤��ʧ��,�������������Ƿ�����!");
		flag = FALSE;
	}
}


void BiliReg::OnBnClickedReg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	Vdcode.MakeUpper();//��֤��ת����д
	BiliThreadRun dlg;
	m_pThrd->PostThreadMessageW(WM_THVDCODE, (WPARAM)this, (LPARAM)&dlg);
	INT_PTR pr = dlg.DoModal();
	if (pr == IDCANCEL)
	{
	}
	else if (pr == IDOK)
	{
	}
	
	GetParent()->SendMessage(WM_REGLOGIN, 0, 0);
}


void BiliReg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


BOOL BiliReg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	ModifyStyleEx(0, WS_EX_LAYERED /*| WS_EX_TRANSPARENT*/);
	SetLayeredWindowAttributes(0, 220, LWA_ALPHA);

//	GetVdcodeHbmp();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void BiliReg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


void BiliReg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	if (flag == TRUE)
	{
		CImage image;
		image.Attach(hBmp);
		image.Draw(GetDlgItem(IDC_VDCODESHOW)->GetDC()->m_hDC, CRect(0, 0, 110, 30));
		hBmp = image.Detach();
	}
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void BiliReg::OnBnClickedFill()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (FILL == TRUE)
	{
		UpdateData(TRUE);
		if (Email.GetLength() == 0)
		{
			srand((unsigned)time(NULL));
			Email.Format(L"%d%d%d%d%d%d%d%d%d%d@qq.com", rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10, rand() % 10);
		}
		if (Uname.GetLength() == 0)
		{
			srand((unsigned)time(NULL));
			char name[2 * 5 + 1];
			int iRange1 = 0xf7 - 0xb0;
			int iRange2 = 0xfe - 0xa1;
			for (int i = 0; i < 5; i++)
			{
				BYTE iCode1 = rand() % iRange1 + 0xb0;
				BYTE iCode2 = rand() % iRange2 + 0xa1;
				name[2 * i] = iCode1;
				name[2 * i + 1] = iCode2;
			}
			name[2 * 5] = '\0';
			Uname = name;
		}
		if (Pwd.GetLength() == 0)
		{
			Pwd = L"12345678";
		}
		UpdateData(FALSE);
	}
	else
	{
		Email = L"";
		Uname = L"";
		Pwd = L"";
		UpdateData(FALSE);
	}
}


void BiliReg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	CDialogEx::OnOK();
	DestroyWindow();
}


void BiliReg::GetVdcodeHbmp()
{
	BiliThreadRun dlg;
	m_pThrd->PostThreadMessageW(WM_THVDCODE, (WPARAM)this, (LPARAM)&dlg);
	INT_PTR pr = dlg.DoModal();
	if (pr == IDCANCEL)
	{
	}
	else if (pr == IDOK)
	{
	}
}


void BiliReg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliReg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
//	delete this;
}


void BiliReg::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::PostNcDestroy();
	delete this;
}

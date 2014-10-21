// BiliReg.cpp : 实现文件
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BiliReg.h"
#include "afxdialogex.h"


// BiliReg 对话框

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


// BiliReg 消息处理程序


void BiliReg::OnBnClickedGetchemail()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ATL::CAtlString res;
	Check((ATL::CAtlString)Email, 0, res);
	MessageBox(res);
}


void BiliReg::OnBnClickedChuname()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ATL::CAtlString res;
	Check((ATL::CAtlString)Uname, 1, res);
	MessageBox(res);
}


void BiliReg::OnBnClickedChpwd()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ATL::CAtlString res;
	Check((ATL::CAtlString)Pwd, 2, res);
	MessageBox(res);
}


void BiliReg::OnBnClickedGetvdcode()
{
	// TODO:  在此添加控件通知处理程序代码
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
		MessageBox(L"获取验证码失败,请检测网络连接是否正常!");
		flag = FALSE;
	}
}


void BiliReg::OnBnClickedReg()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Vdcode.MakeUpper();//验证码转化大写
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
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL BiliReg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	ModifyStyleEx(0, WS_EX_LAYERED /*| WS_EX_TRANSPARENT*/);
	SetLayeredWindowAttributes(0, 220, LWA_ALPHA);

//	GetVdcodeHbmp();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void BiliReg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


void BiliReg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	if (flag == TRUE)
	{
		CImage image;
		image.Attach(hBmp);
		image.Draw(GetDlgItem(IDC_VDCODESHOW)->GetDC()->m_hDC, CRect(0, 0, 110, 30));
		hBmp = image.Detach();
	}
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void BiliReg::OnBnClickedFill()
{
	// TODO:  在此添加控件通知处理程序代码
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
	// TODO:  在此添加专用代码和/或调用基类
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
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
	DestroyWindow();
}


void BiliReg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
//	delete this;
}


void BiliReg::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();
	delete this;
}

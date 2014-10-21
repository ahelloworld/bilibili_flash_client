
// BilibiliDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Bilibili.h"
#include "BilibiliDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBilibiliDlg 对话框



CBilibiliDlg::CBilibiliDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBilibiliDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBilibiliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBilibiliDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_MESSAGE(WM_SETBG, SetBG)
	ON_MESSAGE(WM_CHANGEBG, ChangeBG)
	ON_MESSAGE(WM_REG, Reg)
	ON_MESSAGE(WM_LOGIN, Login)
	ON_MESSAGE(WM_OPENVIDEO, OpenVideo)
	ON_MESSAGE(WM_REGLOGIN, RegLogin)
	ON_MESSAGE(WM_LOGINOK, LoginOk)
END_MESSAGE_MAP()

// CBilibiliDlg 消息处理程序

BOOL CBilibiliDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

//	_CrtSetBreakAlloc();



	// 初始化gdi+
	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);

	flag = FALSE;
	r = 100, g = 195, b = 241;
	a = 240;
	person = 0;

	// 半透明
	ModifyStyleEx(0, WS_EX_LAYERED /*| WS_EX_TRANSPARENT*/);
	SetLayeredWindowAttributes(RGB(250, 250, 250), a, LWA_ALPHA | LWA_COLORKEY);

	// 初始化标签栏和列表栏

	listdlg = new BiliList();// 列表框
	listdlg->Create(IDD_LIST);

	pagedlg = new BiliPage();// 标签栏
	pagedlg->Create(IDD_PAGE);

	facedlg = new BiliFace();// 头像信息
	facedlg->Create(IDD_FACE);

	menudlg = new BiliMenu();// 菜单栏
	menudlg->Create(IDD_MENU);

	regdlg = new BiliReg();// 注册窗口
	regdlg->Create(IDD_REGBOX);

	playerdlg = new BiliPlayer();// 加载播放器
	playerdlg->Create(IDD_PLAYER);

	logindlg = new BiliLogin();// 登录界面
	logindlg->Create(IDD_LOGIN);

	// 线程
	m_pThrd = AfxBeginThread(RUNTIME_CLASS(BiliThread));
	logindlg->m_pThrd = m_pThrd;
	regdlg->m_pThrd = m_pThrd;

	// 显示
	listdlg->ShowWindow(SW_SHOWNORMAL);
	pagedlg->ShowWindow(SW_SHOWNORMAL);
	menudlg->ShowWindow(SW_HIDE);
	regdlg->ShowWindow(SW_HIDE);
	playerdlg->ShowWindow(SW_HIDE);
	logindlg->ShowWindow(SW_HIDE);

	facedlg->ShowWindow(SW_SHOWNORMAL);

	// 排版
	CRect rc1, rc2;
	listdlg->GetClientRect(rc1);
	pagedlg->GetClientRect(rc2);

	// 表宽:rc.Width(),客户端宽:rc.Width()+2*tvW(小电视边框宽),标签栏宽:rc.Width()-40,bili娘宽:biliW
	// 表高:rc.Height(),客户端高:rc.Height()+60+tvH(小电视底边宽)+tvL(小电视脚高),标签栏高:自调节,bili娘高:biliH

	tvW = 40, tvH = 40, tvL = 30;
	biliW = 120, biliH = 180;

	SetWindowPos(&wndTop, 0, 0, rc1.Width() + 2 * tvW, rc1.Height() + biliH + tvH + tvL, SWP_NOMOVE);// 客户端大小调整

	listdlg->MoveWindow(tvW, biliH, rc1.Width(), rc1.Height()); // 列表框位置调整
	
	pagedlg->SetWindowPos(&pagedlg->wndBottom, tvW, biliH - rc2.Height(), rc1.Width() - biliW + tvW, rc2.Height(), NULL);// 标签栏大小位置调整


	facedlg->SetWindowPos(&facedlg->wndBottom, tvW, 10, 0, 0, SWP_NOSIZE);

	menudlg->SetWindowPos(&menudlg->wndBottom, 0, 0, 100, 250, SWP_NOMOVE);// 菜单大小调整

	playerdlg->SetWindowPos(&playerdlg->wndBottom, 0, 0, rc1.Width(), rc1.Height(), SWP_NOMOVE);// player位置大小调整

	playerdlg->player.put_Width(rc1.Width());
	playerdlg->player.put_Height(rc1.Height());

	PaintBackground(255, r, g, b);

	pagedlg->BackgroundSave(r, g, b);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBilibiliDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(BackgroundBitmap);
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBilibiliDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBilibiliDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	if (flag == TRUE)
	{
		menudlg->ShowWindow(SW_HIDE);
		flag = FALSE;
	}
	else if (point.x > rc.Width() - 70 && point.x < rc.Width() - 40 && point.y > rc.Height() - 65 && point.y < rc.Height() - 35)
	{
		CPoint p = point;
		ClientToScreen(&p);
//		menudlg->MoveWindow(p.x - 100, p.y - 250, 100, 250);// 菜单位置调整
		menudlg->SetWindowPos(&menudlg->wndBottom, p.x - 100, p.y - 250, 0, 0, SWP_NOSIZE);
		//menudlg->BringWindowToTop();
		//menudlg->SetForegroundWindow();
		menudlg->ShowWindow(SW_SHOW);
//		InvalidateRect(NULL, FALSE);
		CPaintDC dc(this);
		dc.Draw3dRect(rc.Width() - 70, rc.Height() - 65, 30, 30, RGB(40, 40, 40), RGB(220, 220, 220));
		flag = TRUE;
	}
	else
	{
		menudlg->ShowWindow(SW_HIDE);
		if (point.x > rc.Width() - 40 && point.x < rc.Width() - 10 && point.y > biliH - 30 && point.y < biliH)
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}



void CBilibiliDlg::PaintBackground(int a_, int r_, int g_, int b_)
{
	::DeleteObject(BackgroundBitmap);

	CPaintDC dc(this);

	int x = 0, y = biliH - tvH, w = rc.Width() - 1, h = rc.Height() - tvL - biliH + tvH - 1;// 圆角矩形

	int lx1 = rc.Width() / 4 - 25, lx2 = 3 * rc.Width() / 4 - 25, ly = rc.Height() - 60;

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	memDC.SelectObject(&bmp);

	Gdiplus::Graphics memGr(memDC.m_hDC);

	Gdiplus::Pen pen(Gdiplus::Color(a_, r_, g_, b_), 1);
	Gdiplus::SolidBrush brush(Gdiplus::Color(a_, r_, g_, b_));

	Gdiplus::SolidBrush colorkey(Gdiplus::Color(250, 250, 250));

	memGr.FillRectangle(&colorkey, 0, 0, rc.Width(), rc.Height());

	int offset_x = 20, offset_y = 20;
	// 小圆脚
	memGr.DrawEllipse(&pen, lx1, ly, 50, 60);
	memGr.DrawEllipse(&pen, lx2, ly, 50, 60);
	memGr.FillEllipse(&brush, lx1, ly, 50, 60);
	memGr.FillEllipse(&brush, lx2, ly, 50, 60);

	memGr.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	// 圆角矩形
	memGr.DrawLine(&pen, x + offset_x, y, w - offset_x, y);
	// 画矩形下面的边  
	memGr.DrawLine(&pen, x + offset_x, y + h, w - offset_x, y + h);
	// 画矩形左面的边  
	memGr.DrawLine(&pen, x, y + offset_y, x, y + h - offset_y);
	// 画矩形右面的边  
	memGr.DrawLine(&pen, x + w, y + offset_y, x + w, y + h - offset_y);
	// 画矩形左上角的圆角  
	memGr.DrawArc(&pen, x, y, offset_x * 2, offset_y * 2, 180, 90);
	// 画矩形右下角的圆角  
	memGr.DrawArc(&pen, x + w - offset_x * 2, y + h - offset_y * 2, offset_x * 2, offset_y * 2, 360, 90);
	// 画矩形右上角的圆角  
	memGr.DrawArc(&pen, x + w - offset_x * 2, y, offset_x * 2, offset_y * 2, 270, 90);
	// 画矩形左下角的圆角  
	memGr.DrawArc(&pen, x, y + h - offset_y * 2, offset_x * 2, offset_y * 2, 90, 90);
	// 填充三个直角矩形
	memGr.FillRectangle(&brush, x, y + offset_y, w, h - offset_y * 2);
	memGr.FillRectangle(&brush, x + offset_x, y, w - offset_x * 2, h);
	// 填充四个角上的扇形区  
	// 填充左上角扇形  
	int offset_pie = 2;
	memGr.FillPie(&brush, x, y, offset_x * 2 + offset_pie, offset_y * 2 + offset_pie, 180, 90);
	// 填充右下角的扇形  
	memGr.FillPie(&brush, x + w - (offset_x * 2 + offset_pie), y + h - (offset_y * 2 + offset_pie), offset_x * 2 + offset_pie, offset_y * 2 + offset_pie, 360, 90);
	// 填充右上角的扇形  
	memGr.FillPie(&brush, x + w - (offset_x * 2 + offset_pie), y, (offset_x * 2 + offset_pie), (offset_y * 2 + offset_pie), 270, 90);
	// 填充左下角的扇形  
	memGr.FillPie(&brush, x, y + h - (offset_x * 2 + offset_pie), (offset_x * 2 + offset_pie), (offset_y * 2 + offset_pie), 90, 90);

	if (person == 0)
	{
		Gdiplus::Image image(L"bilibili_33.png");
		memGr.DrawImage(&image, rc.Width() - biliW, 0, biliW, biliH);
	}
	else
	{
		Gdiplus::Image image(L"bilibili_22.png");
		memGr.DrawImage(&image, rc.Width() - biliW, 10, biliW, biliH - 10);
	}

	Gdiplus::Image image_min(L"min.png");
	memGr.DrawImage(&image_min, rc.Width() - 40, biliH - 30, 30, 30);

	Gdiplus::Image image_menu(L"menu.png");
	memGr.DrawImage(&image_menu, rc.Width() - 70, rc.Height()- 65, 30, 30);

	//Gdiplus::Image image_logo(L"bilibililogo.png");
	//memGr.DrawImage(&image_logo, 20, rc.Height() - tvL - tvW, 80, 40);
	//Gdiplus::Image image_logo(L"tvlogo.png");
	//memGr.DrawImage(&image_logo, rc.Width() - 60, rc.Height() - tvL - tvW, 40, 40);

	BackgroundBitmap = (HBITMAP*)bmp.Detach();
	memDC.DeleteDC();
	bmp.DeleteObject();
	InvalidateRect(NULL, FALSE);
}


void CBilibiliDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	GetClientRect(rc);
	// TODO:  在此处添加消息处理程序代码
}

LRESULT CBilibiliDlg::SetBG(WPARAM wParam, LPARAM lParam)
{
	BiliBGSet dlg;
	int r_ = r;
	int g_ = g;
	int b_ = b;
	int a_ = a;
	int temp = person;

	dlg.r = r;
	dlg.g = g;
	dlg.b = b;
	dlg.a = a;
	dlg.person = person;
	
	CRect rcw = rc;
	ClientToScreen(&rcw);
	dlg.x = rcw.right + 5;
	dlg.y = rcw.bottom - 30;

	dlg.SetBackgroundColor(RGB(r, g, b));

	INT_PTR pr = dlg.DoModal();
	if (pr == IDCANCEL)
	{
		r = r_;
		g = g_;
		b = b_;
		a = a_;
		person = temp;
		PaintBackground(255, r, g, b);
		pagedlg->BackgroundSave(r, g, b);
		SetLayeredWindowAttributes(RGB(250, 250, 250), a, LWA_ALPHA | LWA_COLORKEY);
	}
	else if (pr == IDOK)
	{
		/*r = dlg.R_POS;
		g = dlg.G_POS;
		b = dlg.B_POS;
		a = dlg.A_POS;*/
	}
	return 0;
}

LRESULT CBilibiliDlg::ChangeBG(WPARAM wParam, LPARAM lParam)
{
	if (lParam == 0)
	{
		r = LOBYTE(LOWORD(wParam));
		g = HIBYTE(LOWORD(wParam));
		b = LOBYTE(HIWORD(wParam));
		//a = HIBYTE(HIWORD(wParam));
		PaintBackground(255, r, g, b);
		pagedlg->BackgroundSave(r, g, b);
		//SetLayeredWindowAttributes(RGB(250, 250, 250), a, LWA_ALPHA | LWA_COLORKEY);
	}
	else if (lParam == 1)
	{
		if (person != wParam)
		{
			person = wParam;
			PaintBackground(255, r, g, b);
		}
	}
	else if (lParam == 2)
	{
		a = wParam;
		SetLayeredWindowAttributes(RGB(250, 250, 250), a, LWA_ALPHA | LWA_COLORKEY);
	}
	return 0;
}

void CBilibiliDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	Gdiplus::GdiplusShutdown(m_pGdiToken);
	/*listdlg->DestroyWindow();
	pagedlg->DestroyWindow();
	regdlg->DestroyWindow();
	playerdlg->DestroyWindow();
	facedlg->DestroyWindow();
	logindlg->DestroyWindow();
	menudlg->DestroyWindow();*/
	
	m_pThrd->Delete();
	CDialogEx::OnOK();
}

LRESULT CBilibiliDlg::Reg(WPARAM wParam, LPARAM lParam)
{
	CRect rcw = rc;
	ClientToScreen(&rcw);
	regdlg->SetWindowPos(&regdlg->wndBottom, rcw.right +  5, rcw.top + biliH - tvH, 0, 0, SWP_NOSIZE);
	regdlg->Email = L"";
	regdlg->Uname = L"";
	regdlg->Pwd = L"";
	regdlg->Vdcode = L"";
	regdlg->FILL = FALSE;
	regdlg->UpdateData(FALSE);
	regdlg->GetVdcodeHbmp();
	regdlg->ShowWindow(SW_SHOW);
	return 0;
}

LRESULT CBilibiliDlg::Login(WPARAM wParam, LPARAM lParam)
{
	logindlg->CenterWindow();
	logindlg->ShowWindow(SW_SHOW);
	return 0;
}

LRESULT CBilibiliDlg::OpenVideo(WPARAM wParam, LPARAM lParam)
{
	BiliOpenVideo dlg;
	dlg.SetBackgroundColor(RGB(230, 250, 250));
	INT_PTR pr = dlg.DoModal();
	if (pr == IDCANCEL)
	{

	}
	else if (pr == IDOK)
	{
		CString avnum = dlg.avnum;
		ATL::CAtlString url;
		GetVideoCid((ATL::CAtlString)avnum, (ATL::CAtlString)avnum, url);
		listdlg->ShowWindow(SW_HIDE);
		playerdlg->Player((CString)url);
		playerdlg->SetWindowPos(&playerdlg->wndBottom, rc.left + tvW, biliH, 0, 0, SWP_NOSIZE);// 位置调整
		playerdlg->ShowWindow(SW_SHOW);
	}
	return 0;
}

LRESULT CBilibiliDlg::RegLogin(WPARAM wParam, LPARAM lParam)
{
	logindlg->EMAIL = regdlg->Email;
	logindlg->PWD = regdlg->Pwd;
	logindlg->Login();
	regdlg->OnOK();
	return 0;
}

LRESULT CBilibiliDlg::LoginOk(WPARAM wParam, LPARAM lParam)
{
	CString coins;
	coins.Format(L"%.1f", logindlg->coins);
	if (logindlg->hBmp != NULL)
	{
		::DeleteObject(facedlg->bmp);
		facedlg->bmp = logindlg->hBmp;
	}
	facedlg->BackgroundSave((CString)logindlg->name, coins);
	return 0;
}
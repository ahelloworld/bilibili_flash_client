
// BilibiliDlg.h : 头文件
//

#pragma once

// areo
#include <dwmapi.h>
#include "afxcmn.h"
#pragma comment (lib, "dwmapi.lib")

#include "BiliList.h"
#include "BiliPage.h"
#include "BiliMenu.h"
#include "BiliBGSet.h"
#include "BiliReg.h"
#include "BiliLogin.h"
#include "BiliOpenVideo.h"
#include "BiliPlayer.h"
#include "BiliFace.h"

#include "BiliThread.h"

// gdi+
#include <gdiplus.h> 
#pragma comment(lib,"gdiplus.lib")

// 线程支持
#include "BiliThread.h"


// CBilibiliDlg 对话框
class CBilibiliDlg : public CDialogEx
{
// 构造
public:
	CBilibiliDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BILIBILI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	BiliList *listdlg;
	BiliPage *pagedlg;
	BiliMenu *menudlg;
	BiliReg *regdlg;
	BiliPlayer *playerdlg;
	BiliFace *facedlg;
	BiliLogin *logindlg;


	ULONG_PTR m_pGdiToken;// gdi+

	CWinThread* m_pThrd; // 线程支持

	int tvW, tvH, tvL, biliW, biliH;// 位置控制

	HBITMAP* BackgroundBitmap;// 保存背景

	CRect rc;

	int r, g, b, a, person;// 可修改的状态

	BOOL flag; // 是否按下

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void PaintBackground(int a, int r, int g, int b);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT SetBG(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT ChangeBG(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT Reg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT Login(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OpenVideo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT RegLogin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT LoginOk(WPARAM wParam, LPARAM lParam);
	virtual void OnOK();
};

#pragma once

// gdi+
#include <gdiplus.h> 
#pragma comment(lib,"gdiplus.lib")

// BiliPage 对话框

class BiliPage : public CDialogEx
{
	DECLARE_DYNAMIC(BiliPage)

public:
	BiliPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BiliPage();

// 对话框数据
	enum { IDD = IDD_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	int pages;
	CRect rc;
	HBITMAP* BackgroundBitmap;// 保存背景

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void BackgroundSave(int r_, int g_, int b_);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
};

#pragma once

#include "BiliThreadRun.h"

// BiliLogin 对话框

class BiliLogin : public CDialogEx
{
	DECLARE_DYNAMIC(BiliLogin)

public:
	BiliLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BiliLogin();

// 对话框数据
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnOK();
	CString EMAIL;
	CString PWD;
	int mid, rank, sex;
	double coins;
	HBITMAP hBmp;
	ATL::CAtlString name;
	void Login();
	afx_msg void OnBnClickedOk();
	CWinThread *m_pThrd;
	virtual void OnCancel();
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
};

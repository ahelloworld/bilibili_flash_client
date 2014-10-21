#pragma once
#include "afxcmn.h"


// BiliThreadRun 对话框

class BiliThreadRun : public CDialogEx
{
	DECLARE_DYNAMIC(BiliThreadRun)

public:
	BiliThreadRun(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BiliThreadRun();

// 对话框数据
	enum { IDD = IDD_THRUN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_crtlProgress;
	CString state;
	int size;
	afx_msg LRESULT OnSetSize(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetState(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetProgress(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
};

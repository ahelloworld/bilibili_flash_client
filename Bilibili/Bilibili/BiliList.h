#pragma once
#include "afxcmn.h"


// BiliList 对话框

class BiliList : public CDialogEx
{
	DECLARE_DYNAMIC(BiliList)

public:
	BiliList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BiliList();

// 对话框数据
	enum { IDD = IDD_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;

	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void PostNcDestroy();
};

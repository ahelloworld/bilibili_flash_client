#pragma once
#include "explorer.h"

#include <shlguid.h>

// BiliPlayer 对话框

class BiliPlayer : public CDialogEx
{
	DECLARE_DYNAMIC(BiliPlayer)

public:
	BiliPlayer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BiliPlayer();

// 对话框数据
	enum { IDD = IDD_PLAYER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CExplorer player;
	virtual BOOL OnInitDialog();
	void Player(CString &url);
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
};

#pragma once
#include "explorer.h"

#include <shlguid.h>

// BiliPlayer �Ի���

class BiliPlayer : public CDialogEx
{
	DECLARE_DYNAMIC(BiliPlayer)

public:
	BiliPlayer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BiliPlayer();

// �Ի�������
	enum { IDD = IDD_PLAYER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

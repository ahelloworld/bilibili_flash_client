#pragma once

#define menu_num 8

// BiliMenu �Ի���

class BiliMenu : public CDialogEx
{
	DECLARE_DYNAMIC(BiliMenu)

public:
	BiliMenu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BiliMenu();

// �Ի�������
	enum { IDD = IDD_MENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	CString menu[menu_num];
	HBITMAP* BackgroundBitmap;
	CRect rc;

	int line;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void BackgroundSave();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
};

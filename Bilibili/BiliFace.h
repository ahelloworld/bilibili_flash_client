#pragma once
#include "afxwin.h"


// BiliFace 对话框

class BiliFace : public CDialogEx
{
	DECLARE_DYNAMIC(BiliFace)

public:
	BiliFace(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BiliFace();

// 对话框数据
	enum { IDD = IDD_FACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_face;
	HBITMAP bmp;
	HBITMAP* BackgroundBitmap;
	afx_msg void OnPaint();
	CRect rc;
	void BackgroundSave(CString &name, CString &coins);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
};

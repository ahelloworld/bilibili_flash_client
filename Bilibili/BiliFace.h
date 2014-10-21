#pragma once
#include "afxwin.h"


// BiliFace �Ի���

class BiliFace : public CDialogEx
{
	DECLARE_DYNAMIC(BiliFace)

public:
	BiliFace(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BiliFace();

// �Ի�������
	enum { IDD = IDD_FACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

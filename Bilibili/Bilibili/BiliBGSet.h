#pragma once
#include "afxcmn.h"


// BiliBGSet �Ի���

class BiliBGSet : public CDialogEx
{
	DECLARE_DYNAMIC(BiliBGSet)

public:
	BiliBGSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BiliBGSet();

	int r, g, b, a, person;

// �Ի�������
	enum { IDD = IDD_BACKGROUNDSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int R_POS;
	int G_POS;
	int B_POS;
	int A_POS;
	int x;
	int y;
	CSliderCtrl SETR;
	CSliderCtrl SETG;
	CSliderCtrl SETB;
	CSliderCtrl SETA;
	afx_msg void OnNMReleasedcaptureR(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureG(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureB(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureA(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClicked22();
	afx_msg void OnBnClicked33();
};

#pragma once

#include "BiliThreadRun.h"

// BiliReg �Ի���

class BiliReg : public CDialogEx
{
	DECLARE_DYNAMIC(BiliReg)

public:
	BiliReg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BiliReg();

// �Ի�������
	enum { IDD = IDD_REGBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGetchemail();
	afx_msg void OnBnClickedChuname();
	afx_msg void OnBnClickedChpwd();
	afx_msg void OnBnClickedGetvdcode();
	afx_msg void OnBnClickedReg();
	afx_msg void OnBnClickedOk();
	CString Email;
	CString Uname;
	CString Pwd;
	CString Vdcode;
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	int x;
	int y;
	HBITMAP hBmp;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedFill();
	BOOL FILL;
	BOOL flag;
	virtual void OnOK();
	void GetVdcodeHbmp();
	CWinThread *m_pThrd;
	virtual void OnCancel();
	afx_msg void OnDestroy();
	virtual void PostNcDestroy();
};

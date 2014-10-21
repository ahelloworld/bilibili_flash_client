
// BilibiliDlg.h : ͷ�ļ�
//

#pragma once

// areo
#include <dwmapi.h>
#include "afxcmn.h"
#pragma comment (lib, "dwmapi.lib")

#include "BiliList.h"
#include "BiliPage.h"
#include "BiliMenu.h"
#include "BiliBGSet.h"
#include "BiliReg.h"
#include "BiliLogin.h"
#include "BiliOpenVideo.h"
#include "BiliPlayer.h"
#include "BiliFace.h"

#include "BiliThread.h"

// gdi+
#include <gdiplus.h> 
#pragma comment(lib,"gdiplus.lib")

// �߳�֧��
#include "BiliThread.h"


// CBilibiliDlg �Ի���
class CBilibiliDlg : public CDialogEx
{
// ����
public:
	CBilibiliDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BILIBILI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	BiliList *listdlg;
	BiliPage *pagedlg;
	BiliMenu *menudlg;
	BiliReg *regdlg;
	BiliPlayer *playerdlg;
	BiliFace *facedlg;
	BiliLogin *logindlg;


	ULONG_PTR m_pGdiToken;// gdi+

	CWinThread* m_pThrd; // �߳�֧��

	int tvW, tvH, tvL, biliW, biliH;// λ�ÿ���

	HBITMAP* BackgroundBitmap;// ���汳��

	CRect rc;

	int r, g, b, a, person;// ���޸ĵ�״̬

	BOOL flag; // �Ƿ���

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void PaintBackground(int a, int r, int g, int b);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT SetBG(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT ChangeBG(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT Reg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT Login(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OpenVideo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT RegLogin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT LoginOk(WPARAM wParam, LPARAM lParam);
	virtual void OnOK();
};

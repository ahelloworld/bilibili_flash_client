#pragma once


// BiliOpenVideo �Ի���

class BiliOpenVideo : public CDialogEx
{
	DECLARE_DYNAMIC(BiliOpenVideo)

public:
	BiliOpenVideo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BiliOpenVideo();

// �Ի�������
	enum { IDD = IDD_INPUTAVNUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString avnum;
	virtual void OnOK();
};

#pragma once


// BiliOpenVideo 对话框

class BiliOpenVideo : public CDialogEx
{
	DECLARE_DYNAMIC(BiliOpenVideo)

public:
	BiliOpenVideo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BiliOpenVideo();

// 对话框数据
	enum { IDD = IDD_INPUTAVNUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString avnum;
	virtual void OnOK();
};

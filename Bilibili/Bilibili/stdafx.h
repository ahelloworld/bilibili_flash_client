
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#define WM_SETBG WM_USER+1
#define WM_CHANGEBG WM_USER+2
#define WM_REG WM_USER+3
#define WM_LOGIN WM_USER+4
#define WM_OPENVIDEO WM_USER+5
#define WM_REGLOGIN WM_USER+6
#define WM_LOGINOK WM_USER+7

#define WM_THLOGIN WM_USER+8
#define WM_THVDCODE WM_USER+9
#define WM_THREG WM_USER+10

#define WM_SETSIZE WM_USER+12
#define WM_SETSTATE WM_USER+13
#define WM_SETPROGRESS WM_USER+14


#ifdef _DEBUG
#pragma comment(lib, "../Debug/BiliRegDll.lib")
#else
#pragma comment(lib, "../Release/BiliRegDll.lib")
#endif

BOOL GetVdcode(HBITMAP& hBmp);
BOOL Reg(ATL::CAtlString& Email, ATL::CAtlString& Uname, ATL::CAtlString& Pwd, ATL::CAtlString& Vdcode, ATL::CAtlString& res);
BOOL Check(ATL::CAtlString& check, int fmdo, ATL::CAtlString& res);
BOOL Myinfo(ATL::CAtlString& cookie_, int& mid, int& rank, double& coins, int& sex, HBITMAP& hBmp, ATL::CAtlString& name);
BOOL UpdateCookie(ATL::CAtlString& Email, ATL::CAtlString& Pwd);
BOOL GetCurrencylog(ATL::CAtlString& Email, int page, ATL::CAtlString& res);
BOOL GetVideoCid(ATL::CAtlString& Email, ATL::CAtlString& Avnum, ATL::CAtlString& res);

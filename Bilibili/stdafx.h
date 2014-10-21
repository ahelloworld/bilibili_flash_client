
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持









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

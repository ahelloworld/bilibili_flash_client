// BiliRegDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include <assert.h>
#include <atlimage.h>

//#define proxy "127.0.0.1:8888"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	assert(userdata);
	size_t len = size * nmemb;
	((std::string*)userdata)->append(ptr, len);
	return len;
}
 
size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
	assert(userdata);
	size_t len = size * nitems;
	((std::string*)userdata)->append(buffer, len);
	return len;
}

std::string CStringToString(CString& str)
{
	std::string s;
	wchar_t * wszString = str.GetBuffer(0);
	int len = ::WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
	char* szU8 = new char[len + 1];
	::WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), szU8, len, NULL, NULL);
	szU8[len] = '\0';
	s = szU8;
	str.ReleaseBuffer();
	delete []szU8;
	return s;
}

void ConvertToUnicode(std::string& strUtf8,CString& strUnicode)
{
	int len = ::MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len];
	memset(wszGBK, 0, len * 2);
	::MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, (LPWSTR)wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len];
	memset(szGBK, 0, len);
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, szGBK, len, NULL, NULL);

	strUnicode = szGBK;
	delete[] szGBK;
	delete[] wszGBK;
}

void JsonStringFix(std::string& str)
{
	int len = strlen(str.c_str()) + 1;
	char *outch = new char[len];
	WCHAR * wChar = new WCHAR[len];
	wChar[0] = 0;
	::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len, wChar, len);
	::WideCharToMultiByte(CP_ACP, 0, wChar, len, outch, len, 0, 0);
	delete[] wChar;
	char* pchar = outch;
	str = pchar;
	delete[] outch;
//	len = strlen(pchar) + 1;
//	WCHAR outName[MAX_PATH];
//	::MultiByteToWideChar(CP_ACP, 0, pchar, len, outName, len);
}


BOOL InternetExplorer(std::string& url, CURLcode& code, std::string& szbuffer, std::string& szheader_buffer, BOOL Cookie, std::string cookie, BOOL Post, std::string post, int Maxredirs)
{
	CURL *curl;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	std::string useragent = "BiliClient";//使用设备
	std::string encoding = "";//解码方式

	if (curl)
	{
//		curl_easy_setopt(curl, CURLOPT_PROXY, proxy);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);//ssl跳过验证
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		if (Cookie == TRUE)
		{
			curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookie.c_str());
			curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookie.c_str());
		}
		
		if (Post == TRUE)
		{
			curl_easy_setopt(curl, CURLOPT_POST, 1);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());
		}

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
		curl_easy_setopt(curl, CURLOPT_MAXREDIRS, Maxredirs);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_USERAGENT, useragent.c_str());
		curl_easy_setopt(curl, CURLOPT_ENCODING, encoding.c_str());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &szbuffer);

		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &szheader_buffer);

		code = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
	}
	else
	{
		return FALSE;
	}
	curl_global_cleanup();
	return TRUE;
}


BOOL GetPic(std::string& url, HBITMAP& hBmp)
{
	std::string szbuffer;
	std::string szheader_buffer;
	std::string temp = "./cookie/temp.txt";
	CImage image;
	CURLcode code;
	if (InternetExplorer(url, code, szbuffer, szheader_buffer, TRUE, temp, FALSE, "", 5))
	{
		if (CURLE_OK == code)
		{
			int val = szbuffer.size();
			if (val > 0)
			{
				HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, val);
				BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
				assert(pmem);
				memcpy(pmem, szbuffer.c_str(), val);
				IStream* pstm;
				CreateStreamOnHGlobal(m_hMem, TRUE, &pstm);
				assert(pstm);
				image.Load(pstm);
				hBmp = image.Detach();
				GlobalUnlock(m_hMem);
				pstm->Release();
			}
			else
			{
				hBmp = NULL;
				return FALSE;
			}
		}
		else
		{
			hBmp = NULL;
			return FALSE;
		}
	}
	else
	{
		hBmp = NULL;
		return FALSE;
	}
	return TRUE;
}

BOOL GetVdcode(HBITMAP& hBmp)
{
	std::string url = "https://secure.bilibili.com/captcha";//验证码
	if (GetPic(url, hBmp))
		return TRUE;
	else
		return FALSE;
}

BOOL Reg(CString& Email_, CString& Uname_, CString& Pwd_, CString& Vdcode_, CString& res)
{

	std::string url = "https://secure.bilibili.com/register";

	std::string szbuffer;
	std::string szheader_buffer;

	std::string Email = CStringToString(Email_);
	std::string Uname = CStringToString(Uname_);
	std::string Pwd = CStringToString(Pwd_);
	std::string Vdcode = CStringToString(Vdcode_);

	std::string strRequest = "";
	strRequest += "dopost=regok&email=";
	strRequest += Email;
	strRequest += "&uname=";
	strRequest += Uname;
	strRequest += "&userpwd=";
	strRequest += Pwd;
	strRequest += "&userpwdok=";
	strRequest += Pwd;
	strRequest += "&vdcode=";
	strRequest += Vdcode;

	std::string temp = "./cookie/temp.txt";

	CURLcode code;
	if (InternetExplorer(url, code, szbuffer, szheader_buffer, TRUE, temp, TRUE, strRequest, 0))
	{
		if (CURLE_TOO_MANY_REDIRECTS == code || szbuffer.size() == 0)
		{
			std::string s = "Success:\nID(Email):" + Email + "\nPassword:" + Pwd;
			ConvertToUnicode(s, res);
		}
		else
		{
			int start = szbuffer.find("document.write(\"", 0);
			start += 16;
			int end = szbuffer.find("\");", start);
			if ((end - start) != 0)
			{
				std::string s(szbuffer, start, end - start);
				ConvertToUnicode(s, res);
			}
			else
			{
				res = "未知的失败原因!";
			}
			return FALSE;	
		}
	}
	else
	{
		return FALSE;
	}
	std::string save = "./cookie/" + Email + ".txt";
	rename(temp.c_str(), save.c_str());
//	std::ofstream idlist("./idlist/all.txt", std::ios::app);
//	idlist << Email << " " << Uname << " " << Pwd << " " << std::endl;
//	idlist.close();
	return TRUE;
}

BOOL Check(CString& check_, int fmdo_, CString& res)
{
	if (fmdo_ == 2)
	{
		int l = check_.GetLength();
		if (l > 16)
		{
			res = "密码过长!";
		}
		else if (l < 6)
		{
			res = "密码过短!";
		}
		else
		{
			res = "OK";
		}
		return TRUE;
	}

	std::string url = "https://secure.bilibili.com/register?fmdo=";

	std::string szbuffer;
	std::string szheader_buffer;

	std::string check = CStringToString(check_);

	if (fmdo_ == 0)
	{
		url += "checkemail&email=" + check;
	}
	else if (fmdo_ == 1)
	{
		url += "checkuname&userid=" + check;
	}

	CURLcode code;
	if (InternetExplorer(url, code, szbuffer, szheader_buffer, FALSE, "", FALSE, "", 0))
	{
		if (CURLE_OK == code)
		{
			ConvertToUnicode(szbuffer, res);
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL Myinfo(CString& cookie_, int& mid, int& rank, double& coins, int& sex, HBITMAP& hBmp, CString& name)
{
	std::string url = "https://api.bilibili.com/myinfo";

	std::string szbuffer;
	std::string szheader_buffer;

	std::string cookie = "";
	cookie = "./cookie/" + CStringToString(cookie_) + ".txt";

	CURLcode code;
	if (InternetExplorer(url, code, szbuffer, szheader_buffer, TRUE, cookie, FALSE, "", 0))
	{
		if (CURLE_OK == code)
		{
			Json::Reader reader;
			Json::Value root;
			if (reader.parse(szbuffer, root))
			{
				mid = root["code"].asInt();
				if (mid != 0)
				{
					std::string message = root["message"].asString();
					CString name_(message.c_str());
					name = name_;
					return FALSE;
				}
				mid = root["mid"].asInt();
				rank = root["rank"].asInt();
				coins = root["coins"].asDouble();
				std::string uname = root["uname"].asString();
				JsonStringFix(uname);
				CString name_(uname.c_str());
				name = name_;
				std::string face = root["face"].asString();
				if (!GetPic(face, hBmp))
					hBmp = NULL;
				sex = root["sex"].asInt();
			}
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL UpdateCookie(CString& Email_, CString& Pwd_)
{
	std::string url = "https://secure.bilibili.tv/login";

	std::string szbuffer;
	std::string szheader_buffer;

	std::string post = "appkey=0a99fa1d87fdd38c&dopost=login&keeptime=2592000&userid=" + CStringToString(Email_) + "&pwd=" + CStringToString(Pwd_) + "&act=login";

	std::string cookie = "";
	cookie = "./cookie/" + CStringToString(Email_) + ".txt";

	CURLcode code;
	if (InternetExplorer(url, code, szbuffer, szheader_buffer, TRUE, cookie, TRUE, post, 5))
	{
		if (CURLE_OK != code)
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL UpdateCookieWithVdcode(CString& Email_, CString& Pwd_)
{
	std::string url = "https://secure.bilibili.tv/login";

	std::string szbuffer;
	std::string szheader_buffer;

	std::string Email = CStringToString(Email_);
	std::string Pwd = CStringToString(Pwd_);

	std::string post = "keeptime=2592000&userid=" + Email + "&pwd=" + Pwd + "&act=login";

	std::string temp = "./cookie/temp.txt";

	CURLcode code;
	if (InternetExplorer(url, code, szbuffer, szheader_buffer, TRUE, temp, TRUE, post, 5))
	{
		if (CURLE_OK != code)
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}

	std::string save = "./cookie/" + Email + ".txt";
	rename(temp.c_str(), save.c_str());
	return TRUE;
}

BOOL GetCurrencylog(CString& Email_, int page, CString& res)
{
	std::string url = "http://member.bilibili.com/message.do?act=currency_log&page=";
	
	char p[5];
	sprintf_s(p, "%d", page);
	url += p;

	std::string szbuffer;
	std::string szheader_buffer;

	std::string Email = CStringToString(Email_);

	std::string cookie = "";
	cookie = "./cookie/" + Email + ".txt";

	CURLcode code;
	if (InternetExplorer(url, code, szbuffer, szheader_buffer, TRUE, cookie, FALSE, "", 5))
	{
		if (CURLE_OK == code)
		{
			Json::Reader reader;
			Json::Value root;
			if (reader.parse(szbuffer, root))
			{
				int numPages = root["numPages"].asInt();
				root["numPages"] = Json::Value::null;
				
				if (numPages != 0)
				{
					if (page > numPages)
					{
						res = "页已超出范围";
						return FALSE;
					}
					std::string s = "";
					Json::Value::Members member;
					std::string str_temp;
					for (Json::Value::iterator it = root.begin(); it != root.end(); it++)
					{
//						member = (*it).getMemberNames();
//						for (Json::Value::Members::iterator itm = member.begin(); itm != member.end(); itm++){}
						str_temp = (*it)["time"].asString();
						if (str_temp != "")
						{
							s += str_temp + "\t";
							str_temp = (*it)["delta"].asString();
							s += str_temp + "\t";
							str_temp = (*it)["type"].asString();
							if (str_temp == "money")
								s += "硬币\t";
							else if (str_temp == "score")
								s += "积分\t";
							else
								s += "其他\t";
							str_temp = (*it)["reason"].asString();
							JsonStringFix(str_temp);
							s += str_temp + "\t";
							s += "\n";
						}
					}
					CString temp(s.c_str());
					res = temp;
				}
				else
				{
					res = "没有相关记录";
				}
			}
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE; 
}

BOOL GetVideoCid(CString& Email_, CString& avnum_, CString &res)
{
	std::string url = "http://api.bilibili.com/view?appkey=0a99fa1d87fdd38c&id=";

	std::string szbuffer;
	std::string szheader_buffer;

	std::string avnum = CStringToString(avnum_);

	url += avnum;

	std::string Email = CStringToString(Email_);
	

	std::string cookie = "";
	cookie = "./cookie/" + Email + ".txt";

	CURLcode code;
	if (InternetExplorer(url, code, szbuffer, szheader_buffer, TRUE, cookie, FALSE, "", 5))
	{
		if (CURLE_OK == code)
		{
			Json::Reader reader;
			Json::Value root;
			if (reader.parse(szbuffer, root))
			{
				std::string geturl = root["offsite"].asString();
				std::string cid = root["cid"].asString();
				if (geturl != "")
				{
					CString temp(geturl.c_str());
					res = temp;
				}
				else
				{
					geturl = "https://static-s.bilibili.com/play.swf?cid=" + cid + "&aid=" + avnum;
					CString temp(geturl.c_str());
					res = temp;
				}
			}
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL GetFavorite(CString& Email_, int page, CString &res)
{
	std::string url = "http://member.bilibili.com/favorite_manage.do?act=favdata&page=";

	std::string szbuffer;
	std::string szheader_buffer;

	char s[16];
	_itoa_s(page, s, 10);
	url += s;

	std::string Email = CStringToString(Email_);


	std::string cookie = "";
	cookie = "./cookie/" + Email + ".txt";

	CURLcode code;
	if (InternetExplorer(url, code, szbuffer, szheader_buffer, TRUE, cookie, FALSE, "", 5))
	{

	}
	else
	{
		return FALSE;
	}
	return TRUE;
}
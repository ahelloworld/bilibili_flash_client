// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>



// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

#include "curl\curl.h"
#pragma comment(lib,"curllib.lib")


#include "json\json.h"
#ifdef _DEBUG
#pragma comment(lib, "json_d.lib")
#else
#pragma comment(lib, "json.lib")
#endif




#include <string>
//#include <fstream>
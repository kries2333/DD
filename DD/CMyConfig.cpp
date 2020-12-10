#include "pch.h"
#include "CMyConfig.h"


CMyConfig::CMyConfig()
{
}


CMyConfig::~CMyConfig()
{
}

bool CMyConfig::ReadConfigIni(CString Key, LPSTR Context, CString Path, CString Type, CString Delauft)
{
	GetPrivateProfileString(Type, Key, Delauft, Context, MAX_PATH, Path);
	return false;
}

bool CMyConfig::WriteConfigIni(CString Key, CString Context, CString Path, CString Type)
{
	WritePrivateProfileString(Type, Key, Context, Path);
	return false;
}

#pragma once

class CMyConfig
{
public:
	CMyConfig();
	~CMyConfig();
	//∂¡≈‰÷√
	bool ReadConfigIni(CString Key, LPSTR Context, CString Type, CString Path, CString Delauft = "");
	//–¥≈‰÷√
	bool WriteConfigIni(CString Key, CString Context, CString Path, CString Type);
};


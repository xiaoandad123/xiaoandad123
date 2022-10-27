#include <Windows.h>
#include "utils.h"
#include <sstream>

void Convert(const char* strIn, char* strOut, int sourceCodepage, int targetCodepage)
{
	int         len = lstrlenA(strIn);
	int         unicodeLen = MultiByteToWideChar(sourceCodepage, 0, strIn, -1, NULL, 0);
	wchar_t     pUnicode[1024] = { 0 };
	MultiByteToWideChar(sourceCodepage, 0, strIn, -1, (LPWSTR)pUnicode, unicodeLen);


	BYTE        pTargetData[2048] = { 0 };
	int         targetLen = WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char*)pTargetData, 0, NULL, NULL);
	WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char*)pTargetData, targetLen, NULL, NULL);
	lstrcpyA(strOut, (char*)pTargetData);
}

void UTF8ToAnsi(PCHAR Src, PCHAR Dst)
{
	Convert(Src, Dst, CP_UTF8, CP_ACP);
}

void AnsiToUTF8(PCHAR Src, PCHAR Dst)
{
	Convert(Src, Dst, CP_ACP, CP_UTF8);
}

void StringSplit(std::string str, char split, std::vector<std::string>& res)
{
	std::istringstream iss(str);	// 输入流
	std::string token;			// 接收缓冲区
	while (getline(iss, token, split))	// 以split为分隔符
	{
		res.push_back(token);
	}
}

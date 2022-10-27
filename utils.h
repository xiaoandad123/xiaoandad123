#pragma once
#include <string>
#include <codecvt>
#include <vector>

void UTF8ToAnsi(PCHAR Src, PCHAR Dst);
void AnsiToUTF8(PCHAR Src, PCHAR Dst);

void StringSplit(std::string str, char split, std::vector<std::string>& res);
#include "pch.h"
#include "Utils.h"

using namespace std;
bool Utils::StartsWith(string str, string comp)
{
	string::size_type index = str.find(comp);
	if (index != string::npos && index == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Utils::StartsWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && index == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

wstring Utils::ToWString(string str)
{
	return wstring(str.begin(), str.end());
}

string Utils::ToString(wstring str)
{
	return string(str.begin(), str.end());
}

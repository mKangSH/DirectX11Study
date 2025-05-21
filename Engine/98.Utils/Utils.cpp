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

void Utils::Replace(OUT std::string& str, std::string comp, std::string rep)
{
	std::string temp = str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != std::string::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length(); // Handles case where 'rep' is a substring of 'comp'
	}

	str = temp;
}

void Utils::Replace(OUT std::wstring& str, std::wstring comp, std::wstring rep)
{
	std::wstring temp = str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != std::wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length(); // Handles case where 'rep' is a substring of 'comp'
	}

	str = temp;
}

wstring Utils::ToWString(string str)
{
	return wstring(str.begin(), str.end());
}

string Utils::ToString(wstring str)
{
	return string(str.begin(), str.end());
}

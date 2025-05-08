#pragma once

class Utils
{
public:
	static bool StartsWith(std::string str, std::string comp);
	static bool StartsWith(std::wstring str, std::wstring comp);

	static std::wstring ToWString(std::string str);
	static std::string ToString(std::wstring str);
};


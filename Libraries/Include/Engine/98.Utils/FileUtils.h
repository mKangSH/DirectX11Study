#pragma once

enum FileMode : uint8
{
	Write,
	Read
};

class FileUtils
{
public:
	FileUtils();
	~FileUtils();

	void Open(std::wstring filePath, FileMode mode);

	template <typename T>
	void Write(const T& data)
	{
		assert(_handle != INVALID_HANDLE_VALUE);

		DWORD bytesWritten = 0;
		assert(::WriteFile(_handle, &data, sizeof(T), reinterpret_cast<LPDWORD>(&bytesWritten), nullptr));
	}

	// Specialization for std::string to handle string data correctly
	template<>
	void Write<std::string>(const std::string& data)
	{
		return Write(data);
	}

	void Write(void* data, uint32 dataSize);
	void Write(const std::string& data);

	template<typename T>
	void Read(OUT T& data)
	{
		assert(_handle != INVALID_HANDLE_VALUE);

		DWORD numOfBytes = 0;
		assert(::ReadFile(_handle, &data, sizeof(T), (LPDWORD)&numOfBytes, nullptr));
	}

	template<typename T>
	T Read()
	{
		T data;
		Read(data);
		return data;
	}

	void Read(void** data, uint32 dataSize);
	void Read(OUT std::string& data);

private:
	HANDLE _handle = INVALID_HANDLE_VALUE;
};


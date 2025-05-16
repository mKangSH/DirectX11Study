#pragma once

#include "../../02.Managers/Graphics.h"

template <typename T>
class ConstantBuffer
{
public:
	ConstantBuffer()
	{
	}

public:
	ComPtr<ID3D11Buffer> GetConstantBuffer() const { return _constantBuffer; }

public:
	void CreateBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		{
			desc.Usage = D3D11_USAGE_DYNAMIC; // CPU Write, GPU Read
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.ByteWidth = static_cast<uint32>(sizeof(T));
		}
		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
		assert(SUCCEEDED(hr));
	}

	void UpdateBuffer(const T& data)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ZeroMemory(&mappedResource, sizeof(mappedResource));

		HRESULT hr = DEVICECONTEXT->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		assert(SUCCEEDED(hr));

		memcpy(mappedResource.pData, &data, sizeof(data));
		DEVICECONTEXT->Unmap(_constantBuffer.Get(), 0);
	}

private:
	ComPtr<ID3D11Buffer> _constantBuffer = nullptr;
};


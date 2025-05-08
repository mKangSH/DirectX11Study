#pragma once
#include "ResourceBase.h"

class Texture : public ResourceBase
{
	using Super = ResourceBase;

public:
	explicit Texture(ComPtr<ID3D11Device> device);
	~Texture();

public:
	void CreateShaderResourceView(const std::wstring& path);
	void CreateShaderResourceViewFromMultiPageTiff(const std::wstring& path, bool is3DTexture = false);

public:
	void SetShaderResourceView(ComPtr<ID3D11DeviceContext> deviceContext, uint32 slot);

	ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() { return _shaderResourceView; }
	Vec2 GetSize() { return _size; }

private:
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;

	Vec2 _size = { 0.0f, 0.0f };
};


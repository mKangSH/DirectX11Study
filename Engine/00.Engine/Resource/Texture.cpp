#include "pch.h"
#include "Texture.h"

Texture::Texture(ResourceType type) : Super(type)
{
}

Texture::~Texture()
{
}

void Texture::Load(const std::wstring& path)
{
	_path = path;
	// Check if the file is a multi-page TIFF
	if (path.find(L".tiff") != std::wstring::npos || path.find(L".tif") != std::wstring::npos)
	{
		CreateShaderResourceViewFromMultiPageTiff(path, false);
	}
	else
	{
		CreateShaderResourceView(path);
	}
}

void Texture::Save(const std::wstring& path)
{
}

void Texture::CreateShaderResourceView(const std::wstring& path)
{
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage image;

	HRESULT hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &metadata, image);
	assert(SUCCEEDED(hr));

	hr = ::CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), metadata, _shaderResourceView.GetAddressOf());
	assert(SUCCEEDED(hr));

	_size.x = static_cast<float>(metadata.width);
	_size.y = static_cast<float>(metadata.height);
}

void Texture::CreateShaderResourceViewFromMultiPageTiff(const std::wstring& path, bool is3DTexture)
{
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage image;

	HRESULT hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_ALL_FRAMES, &metadata, image);
	assert(SUCCEEDED(hr));

	DirectX::ScratchImage volumeImage;
	if (is3DTexture)
	{
		hr = volumeImage.Initialize3DFromImages(image.GetImages(), image.GetImageCount());
		assert(SUCCEEDED(hr));

		metadata = volumeImage.GetMetadata();

		hr = ::CreateShaderResourceView(DEVICE.Get(), volumeImage.GetImages(), volumeImage.GetImageCount(), metadata, _shaderResourceView.GetAddressOf());
		assert(SUCCEEDED(hr));
	}
	else
	{
		hr = ::CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), metadata, _shaderResourceView.GetAddressOf());
		assert(SUCCEEDED(hr));
	}	

	_size.x = static_cast<float>(metadata.width);
	_size.y = static_cast<float>(metadata.height);
}

void Texture::SetShaderResourceView(ComPtr<ID3D11DeviceContext> deviceContext, uint32 slot)
{

}
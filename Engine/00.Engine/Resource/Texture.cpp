#include "pch.h"
#include "Texture.h"

Texture::Texture(ComPtr<ID3D11Device> device)
	: Super(ResourceType::Texture), _device(device)
{
}

Texture::~Texture()
{
}

void Texture::CreateShaderResourceView(const std::wstring& path)
{
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage image;

	HRESULT hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &metadata, image);
	assert(SUCCEEDED(hr));

	hr = ::CreateShaderResourceView(_device.Get(), image.GetImages(), image.GetImageCount(), metadata, _shaderResourceView.GetAddressOf());
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

		hr = ::CreateShaderResourceView(_device.Get(), volumeImage.GetImages(), volumeImage.GetImageCount(), metadata, _shaderResourceView.GetAddressOf());
		assert(SUCCEEDED(hr));
	}
	else
	{
		hr = ::CreateShaderResourceView(_device.Get(), image.GetImages(), image.GetImageCount(), metadata, _shaderResourceView.GetAddressOf());
		assert(SUCCEEDED(hr));
	}	

	_size.x = static_cast<float>(metadata.width);
	_size.y = static_cast<float>(metadata.height);
}

void Texture::SetShaderResourceView(ComPtr<ID3D11DeviceContext> deviceContext, uint32 slot)
{

}
#include "pch.h"
#include "Graphics.h"

void Graphics::Init(HWND hwnd)
{
	_hwnd = hwnd;

	_sceneTextureWidth = GAME->GetGameDesc().width;
	_sceneTextureHeight = GAME->GetGameDesc().height;

	// 1. Create Device and SwapChain
	CreateDeviceAndSwapChain();

	// 2. Create UI RenderTargetView
	CreateUIRenderTargetView();

	// 3. Create RenderTargetView
	CreateRenderTargetView();

	// 4. Create DepthStencilView
	CreateDepthStencilView();

	// 5. Set Viewport
	SetViewport();
}

void Graphics::RenderBegin()
{
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), (float*)(&GAME->GetGameDesc().clearColor));
	_deviceContext->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	_deviceContext->RSSetViewports(1, &_viewport);
}

void Graphics::UIRenderBegin()
{
	_deviceContext->OMSetRenderTargets(1, _uiRenderTargetView.GetAddressOf(), nullptr);
	_deviceContext->ClearRenderTargetView(_uiRenderTargetView.Get(), DirectX::Colors::Black);
}

void Graphics::RenderEnd()
{
	HRESULT hr = _swapChain->Present(1, 0);
	assert(SUCCEEDED(hr));
}

void Graphics::UIResize()
{
	float width = GAME->GetGameDesc().width;
	float height = GAME->GetGameDesc().height;
	if (_viewport.Width != width || _viewport.Height != height)
	{
		_uiRenderTargetView = nullptr;
		_swapChain->ResizeBuffers(0, GAME->GetGameDesc().width, GAME->GetGameDesc().height, DXGI_FORMAT_UNKNOWN, 0);

		ID3D11Texture2D* pBackBuffer;
		_swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
		DEVICE->CreateRenderTargetView(pBackBuffer, nullptr, &_uiRenderTargetView);
		pBackBuffer->Release();

		_viewport.Width = width;
		_viewport.Height = height;
	}
}

void Graphics::MainRenderResize()
{
	if (_resizeFlag)
	{
		_resizeFlag = false;

		// Resize the ImGui window to match the game window size
		_renderTargetTexture = nullptr;
		_renderTargetView = nullptr;
		_shaderResourceView = nullptr;

		_depthStencilBuffer = nullptr;
		_depthStencilView = nullptr;

		RECT rect;
		GetClientRect(_hwnd, &rect);

		GAME->GetGameDesc().width = rect.right - rect.left;
		GAME->GetGameDesc().height = rect.bottom - rect.top;

		_sceneTextureWidth = rect.right - rect.left;
		_sceneTextureHeight = rect.bottom - rect.top;

		CreateRenderTargetView();
		CreateDepthStencilView();
	}
}

void Graphics::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	//memset(&desc, 0, sizeof(desc));
	{
		desc.BufferDesc.Width = GAME->GetGameDesc().width;
		desc.BufferDesc.Height = GAME->GetGameDesc().height;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1; // 후면 버퍼의 개수
		desc.OutputWindow = _hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	assert(SUCCEEDED(hr));
}

void Graphics::CreateUIRenderTargetView()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	assert(SUCCEEDED(hr));

	hr = _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _uiRenderTargetView.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void Graphics::CreateRenderTargetView()
{
	// 텍스처 설명자 설정
	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = static_cast<UINT>(_sceneTextureWidth);
	texDesc.Height = static_cast<UINT>(_sceneTextureHeight);
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	// 텍스처 생성
	HRESULT hr = DEVICE->CreateTexture2D(&texDesc, nullptr, _renderTargetTexture.GetAddressOf());
	assert(SUCCEEDED(hr));

	// RTV 생성
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = texDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	hr = DEVICE->CreateRenderTargetView(_renderTargetTexture.Get(), &rtvDesc, &_renderTargetView);
	assert(SUCCEEDED(hr));

	// SRV 생성
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	hr = DEVICE->CreateShaderResourceView(_renderTargetTexture.Get(), &srvDesc, &_shaderResourceView);
	assert(SUCCEEDED(hr));
}

void Graphics::CreateDepthStencilView()
{
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	{
		depthStencilDesc.Width = static_cast<uint32>(_sceneTextureWidth);
		depthStencilDesc.Height = static_cast<uint32>(_sceneTextureHeight);
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;
	}

	HRESULT hr = _device->CreateTexture2D(&depthStencilDesc, nullptr, _depthStencilBuffer.GetAddressOf());
	assert(SUCCEEDED(hr));

	D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;
	ZeroMemory(&depthViewDesc, sizeof(depthViewDesc));
	{
		depthViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthViewDesc.Texture2D.MipSlice = 0;
	}
	hr = _device->CreateDepthStencilView(_depthStencilBuffer.Get(), &depthViewDesc, _depthStencilView.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void Graphics::SetViewport()
{
	_viewport.TopLeftX = 0.0f;
	_viewport.TopLeftY = 0.0f;
	_viewport.Width = GAME->GetGameDesc().width;
	_viewport.Height = GAME->GetGameDesc().height;
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;
}

#pragma once

class Graphics
{
	DECLARE_SINGLETON(Graphics)

public:
	void Init(HWND hwnd);
	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:
	HWND _hwnd = nullptr;

	// DirectX11 Device & SwapChain
	ComPtr<ID3D11Device> _device = nullptr; // »ý¼º
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr; // Rendering
	ComPtr<IDXGISwapChain> _swapChain = nullptr;

	// Render Target View
	ComPtr<ID3D11RenderTargetView> _renderTargetView = nullptr;

	// MISC
	D3D11_VIEWPORT _viewport = { 0 };
};


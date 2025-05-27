#pragma once

class Graphics
{
	DECLARE_SINGLETON(Graphics)

public:
	void Init(HWND hwnd);
	void RenderBegin();
	void UIRenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }
	ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() { return _shaderResourceView; }

	void UIResize();

private:
	void CreateDeviceAndSwapChain();
	void CreateUIRenderTargetView();
	void CreateRenderTargetView();
	void CreateDepthStencilView();
	void SetViewport();

private:
	HWND _hwnd = nullptr;

	// DirectX11 Device & SwapChain
	ComPtr<ID3D11Device> _device = nullptr; // »ý¼º
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr; // Rendering
	ComPtr<IDXGISwapChain> _swapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> _uiRenderTargetView = nullptr;

	D3D11_VIEWPORT _viewport = { 0 };

private:
	// Render Target View
	ComPtr<ID3D11Texture2D> _renderTargetTexture = nullptr;
	ComPtr<ID3D11RenderTargetView> _renderTargetView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;

	// Depth Stencil View
	ComPtr<ID3D11Texture2D> _depthStencilBuffer = nullptr;
	ComPtr<ID3D11DepthStencilView> _depthStencilView = nullptr;
};


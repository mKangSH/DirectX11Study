#pragma once

class ImGuiManager
{
	DECLARE_SINGLETON(ImGuiManager)

public:
	void Init();
	void Update();
	void Render();

public:
	ComPtr<ID3D11RenderTargetView> GetRenderTargetView() { return _renderTargetView; }
	ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() { return _shaderResourceView; }

private:
	void CreateDx11SceneTexture();

	ComPtr<ID3D11Texture2D> _renderTargetTexture = nullptr;

	ComPtr<ID3D11RenderTargetView> _renderTargetView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;
};


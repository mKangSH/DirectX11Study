#pragma once

class IndexBuffer
{
public:
	explicit IndexBuffer(ComPtr<ID3D11Device> device);
	~IndexBuffer();

public:
	ComPtr<ID3D11Buffer> GetBuffer() const { return _indexBuffer; }
	uint32 GetStride() const { return _stride; }
	uint32 GetOffset() const { return _offset; }
	uint32 GetCount() const { return _count; }

	void CreateBuffer(const std::vector<uint32>& indices);

private:
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11Buffer> _indexBuffer = nullptr;

	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;
};


#pragma once

class VertexBuffer
{
public:
	explicit VertexBuffer();
	~VertexBuffer();

public:
	ComPtr<ID3D11Buffer> GetBuffer() const { return _vertexBuffer; }

	uint32 GetStride() const { return _stride; }
	uint32 GetOffset() const { return _offset; }
	uint32 GetCount() const { return _count; }
	uint32 GetSlot() const { return _slot; }

	template<typename T>
	void CreateBuffer(const std::vector<T>& vertices, uint32 slot = 0, bool cpuWrite = false, bool gpuWrite = false)
	{
		_stride = sizeof(T);
		_count = static_cast<uint32>(vertices.size());

		_slot = slot;
		_cpuWrite = cpuWrite;
		_gpuWrite = gpuWrite;

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = static_cast<uint32>(_stride * _count);

		if (_cpuWrite == false && gpuWrite == false)
		{
			desc.Usage = D3D11_USAGE_IMMUTABLE;
		}
		else if (_cpuWrite == true && gpuWrite == false)
		{
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else if (_cpuWrite == false && gpuWrite == true)
		{
			desc.Usage = D3D11_USAGE_DEFAULT;
		}
		else
		{
			desc.Usage = D3D11_USAGE_STAGING;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		}

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		{
			data.pSysMem = vertices.data();
		}

		HRESULT hr = DEVICE->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
		assert(SUCCEEDED(hr));
	}

	void PushData()
	{
		DEVICECONTEXT->IASetVertexBuffers(_slot, 1, _vertexBuffer.GetAddressOf(), &_stride, &_offset);
	}

private:
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;

	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;

	uint32 _slot = 0;
	bool _cpuWrite = false;
	bool _gpuWrite = false;
};


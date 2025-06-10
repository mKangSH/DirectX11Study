#include "pch.h"
#include "InstancingBuffer.h"

InstancingBuffer::InstancingBuffer()
{
	CreateInstanceBuffer(MAX_MESH_INSTANCES);
}

InstancingBuffer::~InstancingBuffer()
{
}

void InstancingBuffer::ClearData()
{
	_data.clear();
}

void InstancingBuffer::AddData(InstancingData& data)
{
	_data.push_back(data);
}

void InstancingBuffer::PushDataToGPU()
{
	const uint32 dataCount = GetCount();
	if (dataCount > _maxCount)
	{
		CreateInstanceBuffer(dataCount);
	}

	D3D11_MAPPED_SUBRESOURCE subResource;

	DEVICECONTEXT->Map(_instanceBuffer->GetBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		::memcpy(subResource.pData, _data.data(), sizeof(InstancingData) * dataCount);
	}
	DEVICECONTEXT->Unmap(_instanceBuffer->GetBuffer().Get(), 0);

	_instanceBuffer->PushData();
}

void InstancingBuffer::CreateInstanceBuffer(uint32 maxCount)
{
	_maxCount = maxCount;
	_instanceBuffer = std::make_shared<VertexBuffer>();

	std::vector<InstancingData> temp(maxCount);
	_instanceBuffer->CreateBuffer(temp, 1, true);
}

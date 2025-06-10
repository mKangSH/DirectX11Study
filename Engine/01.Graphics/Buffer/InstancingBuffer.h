#pragma once

class VertexBuffer;

struct InstancingData
{
	Matrix world;
};

#define MAX_MESH_INSTANCES 500

class InstancingBuffer
{
public:
	InstancingBuffer();
	~InstancingBuffer();

public:
	void ClearData();
	void AddData(InstancingData& data);
	void PushDataToGPU();

private:
	void CreateInstanceBuffer(uint32 maxCount = MAX_MESH_INSTANCES);

public:
	uint32 GetCount() const { return static_cast<uint32>(_data.size()); }
	std::shared_ptr<VertexBuffer> GetInstanceBuffer() const { return _instanceBuffer; }

private:
	//uint64							_instanceId = 0;
	std::shared_ptr<VertexBuffer>	_instanceBuffer;
	uint32							_maxCount = 0;
	std::vector<InstancingData>		_data;
};
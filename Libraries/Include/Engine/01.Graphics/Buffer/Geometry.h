#pragma once

template<typename T>
class Geometry
{
public:
	Geometry() = default;
	~Geometry() = default;

public:
	uint32 GetVertexCount() const { return static_cast<uint32>(_vertices.size()); }
	void* GetVertexData() { return _vertices.data(); }
	const std::vector<T>& GetVertices() const { return _vertices; }

	uint32 GetIndexCount() const { return static_cast<uint32>(_indices.size()); }
	void* GetIndexData() { return _indices.data(); }
	const std::vector<uint32>& GetIndices() const { return _indices; }

public:
	void ReserveVertexCount(uint32 count) { _vertices.reserve(count); }
	void AddVertex(const T& vertex) { _vertices.push_back(vertex); }
	void AddVertices(const std::vector<T>& vertices) { _vertices.insert(_vertices.end(), vertices.begin(), vertices.end()); }
	void SetVertices(const std::vector<T>& vertices) { _vertices = vertices; }

	void ReserveIndexCount(uint32 count) { _indices.reserve(count); }
	void AddIndex(uint32 index) { _indices.push_back(index); }
	void AddIndices(const std::vector<uint32>& indices) { _indices.insert(_indices.end(), indices.begin(), indices.end()); }
	void SetIndices(const std::vector<uint32>& indices) { _indices = indices; }

private:
	std::vector<T> _vertices;
	std::vector<uint32> _indices;
};


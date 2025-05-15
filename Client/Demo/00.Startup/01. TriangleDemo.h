#pragma once
#include "Engine/00.Engine/IExecute.h"

class TriangleDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	std::shared_ptr<Shader> _shader;
	std::vector<VertexData> _vertices;
	std::shared_ptr<VertexBuffer> _buffer;
};


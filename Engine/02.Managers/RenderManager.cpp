#include "pch.h"
#include "RenderManager.h"
#include "../04.Component/Camera.h"

void RenderManager::Init(std::shared_ptr<Shader> shader)
{
	_shader = shader;

	_globalBuffer = std::make_shared<ConstantBuffer<GlobalDesc>>();
	_globalBuffer->CreateBuffer();
	_globalEffectBuffer = _shader->GetConstantBuffer("GlobalBuffer");

	_transformBuffer = std::make_shared<ConstantBuffer<TransformDesc>>();
	_transformBuffer->CreateBuffer();
	_transformEffectBuffer = _shader->GetConstantBuffer("TransformBuffer");
}

void RenderManager::Update()
{
	UploadGlobalDesc(Camera::S_MatView, Camera::S_MatProjection);
}

void RenderManager::UploadGlobalDesc(const Matrix& view, const Matrix& projection)
{
	_globalDesc.View = view;
	_globalDesc.Projection = projection;
	_globalDesc.ViewProjection = view * projection;
	
	_globalBuffer->UpdateBuffer(_globalDesc);
	_globalEffectBuffer->SetConstantBuffer(_globalBuffer->GetConstantBuffer().Get());
}

void RenderManager::UploadTransformDesc(const TransformDesc& desc)
{
	_transformDesc = desc;

	_transformBuffer->UpdateBuffer(_transformDesc);
	_transformEffectBuffer->SetConstantBuffer(_transformBuffer->GetConstantBuffer().Get());
}

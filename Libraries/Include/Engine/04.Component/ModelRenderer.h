#pragma once
#include "Component.h"

class ModelRenderer : public Component
{
	using Super = Component;

public:
	explicit ModelRenderer(std::shared_ptr<class Shader> shader);
	virtual ~ModelRenderer();

	virtual void Update() override;

	void SetModel(std::shared_ptr<class Model> model);
	void SetPass(uint8 pass) { _pass = pass; }

private:
	uint8 _pass = 0;
	std::shared_ptr<class Shader> _shader;
	std::shared_ptr<class Model> _model;
};


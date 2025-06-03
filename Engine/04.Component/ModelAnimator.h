#pragma once
#include "Component.h"

struct AnimTransform
{
	// [] [] [] [] [] [] [] [] ... 255°³ 
	using TransformArrayType = std::array<Matrix, MAX_MODEL_TRANSFORMS>;

	// [] [] [] [] [] [] [] [] ... 510°³
	std::array<TransformArrayType, MAX_MODEL_KEYFRAMES> transforms;
};

class ModelAnimator : public Component
{
	using Super = Component;

public:
	explicit ModelAnimator(std::shared_ptr<class Shader> shader);
	~ModelAnimator();

	virtual void Update() override;

	void SetModel(std::shared_ptr<class Model> model);
	void SetPass(uint8 pass) { _pass = pass; }

private:
	void CreateTexture();
	void CreateAniamtionTransform(uint32 index);

private:
	std::vector<AnimTransform> _animationTransforms;
	ComPtr<ID3D11Texture2D> _texture;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;

private:
	KeyframeDesc _keyframeDesc;
	TweenFrameDesc _tweenFrameDesc;

private:
	uint8 _pass = 0;
	std::shared_ptr<class Shader> _shader;
	std::shared_ptr<class Model> _model;
};




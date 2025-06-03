#include "pch.h"
#include "ModelAnimation.h"

std::shared_ptr<ModelKeyframe> ModelAnimation::GetKeyframe(const std::wstring& name)
{
	auto findit = keyframes.find(name);

	if (findit == keyframes.end())
	{
		return nullptr;
	}

	return findit->second;
}

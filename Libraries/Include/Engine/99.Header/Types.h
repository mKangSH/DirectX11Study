#pragma once

#include <Windows.h>
#include "DirectXMath.h"
#include "../98.Utils/SimpleMath.h"

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;

using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

using Color = DirectX::XMVECTORF32;

using Vec2 = DirectX::SimpleMath::Vector2;
using Vec3 = DirectX::SimpleMath::Vector3;
using Vec4 = DirectX::SimpleMath::Vector4;
using Matrix = DirectX::SimpleMath::Matrix;
using Quaternion = DirectX::SimpleMath::Quaternion;

enum class ComponentType : uint8
{
	Transform,
	MeshRenderer,
	ModelRenderer,
	Camera,
	Animator,
	//Light,
	//Physics,
	//Audio,
	//UI,
	Script,

	Count
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(ComponentType::Count) - 1,
};

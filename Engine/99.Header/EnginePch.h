#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Types.h"
#include "Define.h"

// STL
#include <memory>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

// WIN
#include <windows.h>
#include <assert.h>
#include <optional>

// DirectX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

// DirectXTex
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
using namespace DirectX;
using namespace Microsoft::WRL;

#include <FX11/d3dx11effect.h>

// Libs
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef _DEBUG
	#pragma comment(lib, "DirectXTex/DirectXTex_debug.lib")
	#pragma comment(lib, "FX11/Effects11d.lib")
#else
	#pragma comment(lib, "DirectXTex/DirectXTex.lib")
	#pragma comment(lib, "FX11/Effects11.lib")
#endif

// Managers
#include "../02.Managers/Game.h"
#include "../02.Managers/Graphics.h"
#include "../02.Managers/InputManager.h"
#include "../02.Managers/TimeManager.h"
#include "../02.Managers/ResourceManager.h"
#include "../02.Managers/RenderManager.h"

// Engine
#include "../00.Engine/IExecute.h"

#include "../01.Graphics/Buffer/VertexData.h"
#include "../01.Graphics/Buffer/VertexBuffer.h"
#include "../01.Graphics/Buffer/IndexBuffer.h"
#include "../01.Graphics/Buffer/ConstantBuffer.h"
#include "../01.Graphics/Shader/Shader.h"

#include "../03.SceneObject/SceneObject.h"
#include "../04.Component/Component.h"
#include "../04.Component/Transform.h"

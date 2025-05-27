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
#include <queue>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

// WIN
#include <windows.h>
#include <assert.h>
#include <optional>
#include <shellapi.h>

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

// Assimp
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

// ImGUI
#include "../98.Utils/ImGUI/imgui.h"
#include "../98.Utils/ImGUI/imgui_impl_dx11.h"
#include "../98.Utils/ImGUI/imgui_impl_win32.h"

// Libs
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef _DEBUG
	#pragma comment(lib, "DirectXTex/DirectXTex_debug.lib")
	#pragma comment(lib, "FX11/Effects11d.lib")
	#pragma comment(lib, "Assimp/assimp-vc143-mtd.lib")
#else
	#pragma comment(lib, "DirectXTex/DirectXTex.lib")
	#pragma comment(lib, "FX11/Effects11.lib")
	#pragma comment(lib, "Assimp/assimp-vc143-mt.lib")
#endif

// Managers
#include "../02.Managers/Game.h"
#include "../02.Managers/Graphics.h"
#include "../02.Managers/InputManager.h"
#include "../02.Managers/TimeManager.h"
#include "../02.Managers/ResourceManager.h"
#include "../02.Managers/RenderManager.h"
#include "../02.Managers/ImGuiManager.h"

// Engine
#include "../00.Engine/IExecute.h"

#include "../01.Graphics/Buffer/VertexData.h"
#include "../01.Graphics/Buffer/VertexBuffer.h"
#include "../01.Graphics/Buffer/IndexBuffer.h"
#include "../01.Graphics/Buffer/ConstantBuffer.h"
#include "../01.Graphics/Shader/Shader.h"

#include "../03.SceneObject/SceneObject.h"
#include "../04.Component/Transform.h"
#include "../00.Engine/Resource/Texture.h"
#include "../00.Engine/Resource/Mesh.h"

#include "pch.h"
#include "AssimpTool.h"
#include "../Utils/Converter.h"

void AssimpTool::Init()
{
	{
		std::shared_ptr<Converter> converter = std::make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"House/cottage_fbx.fbx");

		// Memory -> Custom Format (File)
		converter->ExportMaterialData(L"House/House");
		converter->ExportModelData(L"House/House");

		// Custom Format (File) -> Memory
	}

	{
		std::shared_ptr<Converter> converter = std::make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"Wolf/Wolf.fbx");

		// Memory -> Custom Format (File)
		converter->ExportMaterialData(L"Wolf/Wolf");
		converter->ExportModelData(L"Wolf/Wolf");

		// Custom Format (File) -> Memory
	}

	{
		std::shared_ptr<Converter> converter = std::make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"Tank/Tank.fbx");

		// Memory -> CustomData (File)
		converter->ExportMaterialData(L"Tank/Tank");
		converter->ExportModelData(L"Tank/Tank");

		// CustomData (File) -> Memory
	}

	{
		std::shared_ptr<Converter> converter = std::make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"Tower/Tower.fbx");

		// Memory -> CustomData (File)
		converter->ExportMaterialData(L"Tower/Tower");
		converter->ExportModelData(L"Tower/Tower");

		// CustomData (File) -> Memory
	}

	{
		std::shared_ptr<Converter> converter = std::make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"Kachujin/mesh.fbx");

		// Memory -> CustomData (File)
		converter->ExportMaterialData(L"Kachujin/Kachujin");
		converter->ExportModelData(L"Kachujin/Kachujin");

		// CustomData (File) -> Memory
	}
	{
		std::shared_ptr<Converter> converter = std::make_shared<Converter>();
		// FBX -> Memory
		converter->ReadAssetFile(L"Kachujin/Idle.fbx");
		converter->ExportAnimationData(L"Kachujin/Idle");
	}
	{
		std::shared_ptr<Converter> converter = std::make_shared<Converter>();
		// FBX -> Memory
		converter->ReadAssetFile(L"Kachujin/Run.fbx");
		converter->ExportAnimationData(L"Kachujin/Run");
	}
	{
		std::shared_ptr<Converter> converter = std::make_shared<Converter>();
		// FBX -> Memory
		converter->ReadAssetFile(L"Kachujin/Slash.fbx");
		converter->ExportAnimationData(L"Kachujin/Slash");
	}
}

void AssimpTool::Update()
{
}

void AssimpTool::Render()
{
}
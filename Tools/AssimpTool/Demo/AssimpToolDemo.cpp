#include "pch.h"
#include "AssimpToolDemo.h"
#include "../Utils/Converter.h"

void AssimpToolDemo::Init()
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
}

void AssimpToolDemo::Update()
{
}

void AssimpToolDemo::Render()
{
}
#include "pch.h"
#include "AssetBrowser.h"
#include "DirectXScene.h"

AssetBrowser::AssetBrowser() : Super()
{
    _title = "AssetBrowser";
}

AssetBrowser::~AssetBrowser()
{
}

void AssetBrowser::Update()
{
	if (_isVisible)
	{
        Draw();
	}
}

void AssetBrowser::Render()
{

}

void AssetBrowser::Draw()
{
    ImGui::Begin(_title.c_str());

    // Menu bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Add 10000 items"))
            {
            }
            if (ImGui::MenuItem("Clear items"))
            {
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Close", NULL, false, &_isVisible != nullptr))
            {
                _isVisible = false;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Options"))
        {
            ImGui::PushItemWidth(ImGui::GetFontSize() * 10);

            ImGui::SeparatorText("Contents");
            ImGui::Checkbox("Show Type Overlay", &ShowTypeOverlay);
            ImGui::Checkbox("Allow Sorting", &AllowSorting);

            ImGui::SeparatorText("Selection Behavior");
            ImGui::Checkbox("Allow dragging unselected item", &AllowDragUnselected);
            ImGui::Checkbox("Allow box-selection", &AllowBoxSelect);

            ImGui::SeparatorText("Layout");
            ImGui::SliderFloat("Icon Size", &IconSize, 16.0f, 128.0f, "%.0f");
            // ImGui::SameLine(); HelpMarker("Use CTRL+Wheel to zoom");
            ImGui::SliderInt("Icon Spacing", &IconSpacing, 0, 32);
            ImGui::SliderInt("Icon Hit Spacing", &IconHitSpacing, 0, 32);
            ImGui::Checkbox("Stretch Spacing", &StretchSpacing);
            ImGui::PopItemWidth();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
}

#include "pch.h"
#include "VisualSequenceGraph.h"

VisualSequenceGraph::VisualSequenceGraph() : Super()
{
    _title = "Visual Sequence Graph";
}

VisualSequenceGraph::~VisualSequenceGraph()
{
}

void VisualSequenceGraph::Update()
{
	if (_isVisible)
	{
		Draw();
	}
}

void VisualSequenceGraph::Render()
{

}

void VisualSequenceGraph::Draw()
{
	ImGui::Begin("Visual Sequence Graph", &_isVisible);

    ImGui::Checkbox("Enable grid", &_optEnableGrid);
    ImGui::Checkbox("Enable context menu", &_optEnableContextMenu);
    ImGui::Text("Mouse Left: drag to add lines,\nMouse Right: drag to scroll, click for context menu.");

    // Typically you would use a BeginChild()/EndChild() pair to benefit from a clipping region + own scrolling.
    // Here we demonstrate that this can be replaced by simple offsetting + custom drawing + PushClipRect/PopClipRect() calls.
    // To use a child window instead we could use, e.g:
    //      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));      // Disable padding
    //      ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(50, 50, 50, 255));  // Set a background color
    //      ImGui::BeginChild("canvas", ImVec2(0.0f, 0.0f), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoMove);
    //      ImGui::PopStyleColor();
    //      ImGui::PopStyleVar();
    //      [...]
    //      ImGui::EndChild();

    // Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()
    ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
    ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
    if (canvas_sz.x < 50.0f)
    {
        canvas_sz.x = 50.0f;
    }

    if (canvas_sz.y < 50.0f)
    {
        canvas_sz.y = 50.0f;
    }
    ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

    // Draw border and background color
    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
    draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));

    // This will catch our interactions
    ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
    const bool is_hovered = ImGui::IsItemHovered(); // Hovered
    const bool is_active = ImGui::IsItemActive();   // Held
    const ImVec2 origin(canvas_p0.x + _scrolling.x, canvas_p0.y + _scrolling.y); // Lock scrolled origin
    const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);

    // Add first and second point
    if (is_hovered && !_addingLine && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        _points.push_back(mouse_pos_in_canvas);
        _points.push_back(mouse_pos_in_canvas);
        _addingLine = true;
    }

    if (_addingLine)
    {
        _points.back() = mouse_pos_in_canvas;
        if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
            _addingLine = false;
    }

    // Pan (we use a zero mouse threshold when there's no context menu)
    // You may decide to make that threshold dynamic based on whether the mouse is hovering something etc.
    const float mouse_threshold_for_pan = _optEnableContextMenu ? -1.0f : 0.0f;
    if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan))
    {
        _scrolling.x += io.MouseDelta.x;
        _scrolling.y += io.MouseDelta.y;
    }

    // Context menu (under default mouse threshold)
    ImVec2 drag_delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
    if (_optEnableContextMenu && drag_delta.x == 0.0f && drag_delta.y == 0.0f)
    {
        ImGui::OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);
    }
        
    if (ImGui::BeginPopup("context"))
    {
        if (_addingLine)
            _points.resize(_points.size() - 2);
        _addingLine = false;
        if (ImGui::MenuItem("Remove one", NULL, false, _points.Size > 0)) { _points.resize(_points.size() - 2); }
        if (ImGui::MenuItem("Remove all", NULL, false, _points.Size > 0)) { _points.clear(); }
        ImGui::EndPopup();
    }

    // Draw grid + all lines in the canvas
    draw_list->PushClipRect(canvas_p0, canvas_p1, true);
    if (_optEnableGrid)
    {
        const float GRID_STEP = 64.0f;
        for (float x = fmodf(_scrolling.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
        {
            draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
        }
            
        for (float y = fmodf(_scrolling.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
        {
            draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(200, 200, 200, 40));
        }
    }

    for (int n = 0; n < _points.Size; n += 2)
    {
        draw_list->AddLine(ImVec2(origin.x + _points[n].x, origin.y + _points[n].y), ImVec2(origin.x + _points[n + 1].x, origin.y + _points[n + 1].y), IM_COL32(255, 255, 0, 255), 2.0f);
    }
        
    draw_list->PopClipRect();

    ImGui::End();
}
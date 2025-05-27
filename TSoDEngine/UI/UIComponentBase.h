#pragma once

class UIComponentBase
{
public:
	UIComponentBase();
	virtual ~UIComponentBase();

public:
	virtual void Update() {}
	virtual void Render() {}

protected:
	virtual void Draw() abstract;

protected:
	std::string _title = "";
	bool _isVisible = true;
};


#pragma once

class IView
{
private:

public:
	IView() {}
	virtual ~IView() {}
	// pure virtual function
	virtual void Update() = 0;
	virtual void HasFocus() = 0;
};
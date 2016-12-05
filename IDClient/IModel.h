#pragma once
class IModel
{
private:

public:
	IModel() {}
	virtual ~IModel() {}
	// pure virtual function
	virtual void Update() = 0;
};
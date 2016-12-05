#pragma once
#include "IView.h"
#include "ThickWrapper.h"
#include <vector>

class cFileView : public IView
{
private:
	virtual void Update();
	virtual void HasFocus() {}

public:
	cFileView(ThickWrapper thick);
	~cFileView();
	void Draw(ThickWrapper thick);
};
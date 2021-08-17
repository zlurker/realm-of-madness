#pragma once

#include "IClickable.h";
#include "IDraggable.h";

class Window: public IClickable,IDraggable
{
public:
	void OnClick();
	void OnDrag();
};


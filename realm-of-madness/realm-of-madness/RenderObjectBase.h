#pragma once

#include "Vector2.h"
#include <windows.h>  
#include <gl\gl.h>          // Header File For The OpenGL32 Library
#include <gl\glu.h> 

class RenderObjectBase
{
public:
	RenderObjectBase();
	Vector2 objectPosition;
	virtual void RenderObject();
};


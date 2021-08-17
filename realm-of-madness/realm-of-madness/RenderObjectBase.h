#pragma once

#include "Vector3.h"
#include <windows.h>  
#include <gl\gl.h>          // Header File For The OpenGL32 Library
#include <gl\glu.h> 

class RenderObjectBase
{
public:
	Vector3 objectPosition;
	virtual void RenderObject();
};


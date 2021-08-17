#include "RenderObjectBase.h"

RenderObjectBase::RenderObjectBase() {
	objectPosition.x = 100;
	objectPosition.y = 100;
}

void RenderObjectBase::RenderObject() {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 40.0, 0.0);
	glVertex3f(80.0, 40.0, 0.0);
	glVertex3f(80.0, 0.0, 0.0);
	glEnd();
}

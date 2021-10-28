#include "RenderSystem.h"

RenderSystem::RenderSystem(int w, int h) : width(w), height(h) {
	std::cout << "Render system initialised." << std::endl;
	renderObjects.push_back(RenderObjectBase());
	renderObjects.push_back(RenderObjectBase());
}

RenderSystem::~RenderSystem() {

}

GLvoid RenderSystem::ReSizeGLScene(GLsizei width, GLsizei height)     // Resize And Initialize The GL Window
{
	if (height == 0)                                      // Prevent A Divide By Zero By
	{
		height = 1;                                       // Making Height Equal One
	}

	glViewport(0, 0, width, height);                       // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                                   // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1.0f);
	glOrtho(0, width, height, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);                         // Select The Modelview Matrix
	glLoadIdentity();                                   // Reset The Modelview Matrix
}

void RenderSystem::SetHandle(HWND handle) {
	wHandle = handle;
	//::MessageBox(0, L"Handle set.", L"Error", MB_ICONEXCLAMATION | MB_OK);
}

int RenderSystem::InitGL(GLvoid)                                      // All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);               // Black Background
	glClearDepth(1.0f);                                 // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
	return TRUE;                                        // Initialization Went OK
}

void RenderSystem::SetPos(int x, int y) {
	std::lock_guard<std::mutex> lock(lock);
	mx = x;
	my = y;


	offsetTest += 0.001f;
}

bool RenderSystem::RenderSetUp() {

	GLuint      PixelFormat;            // Holds The Results After Searching For A Match

	static  PIXELFORMATDESCRIPTOR pfd =              // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),              // Size Of This Pixel Format Descriptor
		1,                                          // Version Number
		PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
		PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
		PFD_DOUBLEBUFFER,                           // Must Support Double Buffering
		PFD_TYPE_RGBA,                              // Request An RGBA Format
		24,                                       // Select Our Color Depth
		0, 0, 0, 0, 0, 0,                           // Color Bits Ignored
		0,                                          // No Alpha Buffer
		0,                                          // Shift Bit Ignored
		0,                                          // No Accumulation Buffer
		0, 0, 0, 0,                                 // Accumulation Bits Ignored
		32,                                         // 16Bit Z-Buffer (Depth Buffer)  
		0,                                          // No Stencil Buffer
		0,                                          // No Auxiliary Buffer
		PFD_MAIN_PLANE,                             // Main Drawing Layer
		0,                                          // Reserved
		0, 0, 0                                     // Layer Masks Ignored
	};

	if (!(hdc = GetDC(wHandle)))                         // Did We Get A Device Context?
	{
		//KillGLWindow();                             // Reset The Display
		MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}



	if (!(PixelFormat = ChoosePixelFormat(hdc, &pfd))) // Did Windows Find A Matching Pixel Format?
	{
		//KillGLWindow();                             // Reset The Display
		//MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}

	if (!SetPixelFormat(hdc, PixelFormat, &pfd))       // Are We Able To Set The Pixel Format?
	{
		//KillGLWindow();                             // Reset The Display
		//MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}

	if (!(hrc = wglCreateContext(hdc)))               // Are We Able To Get A Rendering Context?
	{
		//KillGLWindow();                             // Reset The Display
		//MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}

	if (!wglMakeCurrent(hdc, hrc))                    // Try To Activate The Rendering Context
	{
		//KillGLWindow();                             // Reset The Display
		//MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}

	//MessageBox(NULL, L"Success.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);

	//ShowWindow(wHandle, SW_SHOW);                       // Show The Window
	SetForegroundWindow(wHandle);                      // Slightly Higher Priority
	SetFocus(wHandle);                                 // Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);                   // Set Up Our Perspective GL Screen

	if (!InitGL())                                  // Initialize Our Newly Created GL Window
	{
		//KillGLWindow();                             // Reset The Display
		//MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;                               // Return FALSE
	}

	return TRUE;
}

void RenderSystem::Render() {
	RenderSetUp();

	//::MessageBox(0, L"Set up completed.", L"Error", MB_ICONEXCLAMATION | MB_OK);
	while (true) {
		Draw();
		SwapBuffers();
	}
}

void RenderSystem::BeginLoop() {
	//RenderSetUp();
	//Render();

	//::MessageBox(0, L"Thread split off.", L"Error", MB_ICONEXCLAMATION | MB_OK);
	renderThread = std::thread(&RenderSystem::Render, this);

	SpaceMatrix test;
	test.CreateNewMatrixElement(Vector2(5, 2), Vector2(8, 2));
	test.CreateNewMatrixElement(Vector2(10, 3), Vector2(6, 2));
	test.CreateNewMatrixElement(Vector2(15, 1), Vector2(14, 2));
	test.GenerateMatrix(0);
	//test.SetMatrixElementLocation(2, Vector2(3, 3));
	//test.SetMatrixElementLocation(2, Vector2(0, 0));
	//RenderSetUp();
	//while (1) {
		//Draw();
		//SwapBuffers();
	//}
}

void RenderSystem::Draw(GLvoid) {
	std::lock_guard<std::mutex> lock(lock);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	//glLoadIdentity();                                   // Reset The Current Modelview Matrix
	/*glTranslatef(-1.5f, 0.0f, -6.0f);						// Move left 1.5 units and into the screen 6.0
	//glRotatef(rtri, 0.0f, 1.0f, 0.0f);						// Rotate the triangle on the y axis
	glBegin(GL_TRIANGLES);								// Start drawing a triangle
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (front)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Left of triangle (front)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(1.0f, -1.0f, 1.0f);					// Right of triangle (front)
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (right)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(1.0f, -1.0f, 1.0f);					// Left of triangle (right)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(1.0f, -1.0f, -1.0f);					// Right of triangle (right)
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (back)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(1.0f, -1.0f, -1.0f);					// Left of triangle (back)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Right of triangle (back)
	glColor3f(1.0f, 0.0f, 0.0f);						// Red
	glVertex3f(0.0f, 1.0f, 0.0f);					// Top Of triangle (left)
	glColor3f(0.0f, 0.0f, 1.0f);						// Blue
	glVertex3f(-1.0f, -1.0f, -1.0f);					// Left of triangle (left)
	glColor3f(0.0f, 1.0f, 0.0f);						// Green
	glVertex3f(-1.0f, -1.0f, 1.0f);					// Right of triangle (left)
	glEnd();		*/									// Done drawing the pyramid
	glLoadIdentity();

	// Reset the current modelview matrix

	GLint viewport[4]; //var to hold the viewport info
	GLdouble modelview[16]; //var to hold the modelview info
	GLdouble projection[16]; //var to hold the projection matrix info
	GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
	GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview); //get the modelview info
	glGetDoublev(GL_PROJECTION_MATRIX, projection); //get the projection matrix info
	glGetIntegerv(GL_VIEWPORT, viewport); //get the viewport info

	winX = (float)mx;
	winY = (float)viewport[3] - (float)my;
	winZ = 0;

	//get the world coordinates from the screen coordinates
	gluUnProject(winX, winY, 0, modelview, projection, viewport, &worldX, &worldY, &worldZ);
	// Move right 1.5 units and into the screen 7.0

	renderObjects[0].objectPosition.x = worldX;
	renderObjects[0].objectPosition.y = worldY;

	for (RenderObjectBase render : renderObjects) {
		glPushMatrix();
		glTranslatef(render.objectPosition.x, render.objectPosition.y, 0);
		render.RenderObject();
		glPopMatrix();
	}
	//glRotatef(20, 20, 20, 1.0f);					// Rotate the quad on the x axis


}

void RenderSystem::SwapBuffers() {
	::SwapBuffers(hdc);
}
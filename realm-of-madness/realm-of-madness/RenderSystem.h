#pragma once
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include <windows.h>        // Header File For Windows
#include <gl\gl.h>          // Header File For The OpenGL32 Library
#include <gl\glu.h> 
#include <thread>
#include <mutex>
//#include "Procedure.h"

class RenderSystem {
public:
	RenderSystem(int w, int h);
	~RenderSystem();

	//void SetUpGL();
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	int mx, my;
	
	int InitGL(GLvoid);
	bool RenderSetUp();
	void Render();
	void Draw(GLvoid);
	void SwapBuffers();
	void BeginLoop();
	void SetHandle(HWND handle);
	void SetPos(int x,int c);
	int width;
	int height;

	

	std::mutex lock;
	GLdouble offsetTest;

	HWND wHandle;
	HDC hdc;
	HGLRC hrc;
	std::thread renderThread;
};
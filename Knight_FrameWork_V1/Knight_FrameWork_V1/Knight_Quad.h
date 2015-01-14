#pragma once
//graphics libraries
#include <glew.h>
#include <wglew.h>
#include <glfw3.h>
#include "SOIL.h"
//default libraries
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>

class Knight_Quad
{
private:
	//Quad variables
	float fPositions[4];
	float fColours[4];
	float fUVs[3];

	GLuint TextureFrames[9];

	bool isMoving = false;

public:
	//Default constructors
	Knight_Quad();
	~Knight_Quad();
	//Custom constructors
	//Knight_Quad(/*Figure out what's needed and add it here*/);

	void SetPosition(float x, float y);
	void SetColor(float R, float G, float B, float Op);
	void SetUVs(float U, float V);
	unsigned int loadTexture(const char* a_pFileName, int & a_iWidth, int & a_iHeight, int a_iBPP);
	//can set up to 10 frames (0-9)
	void SetTexture(int frame, const char* textureName, int width, int height, int bpp);

	void Update();
	//set timer to zero by default. Goes up to 39 (0-39) so reset your clock after that
	void Draw(float timer);
};


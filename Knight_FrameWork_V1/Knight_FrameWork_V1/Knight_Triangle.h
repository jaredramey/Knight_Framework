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

struct Point
{
	float fPositions[4];
	float fColours[4];
	float fUVs[2];
};

class Knight_Triangle
{
private:
	//Triangle variables

	GLuint TextureFrames[9];

	bool isMoving = false;

public:
	//Default Constructors
	Knight_Triangle();
	~Knight_Triangle();
	//Custom constructor
	//Knight_Triangle(/*Figure out whats needed to be added and put it here*/);
	
	bool isLoaded = false;

	Point points[3];

	//Custom Functions
	void SetPosition(int point, float x, float y);
	void SetColor(float R, float G, float B, float Op);
	void SetUVs(int point, float U, float V);
	unsigned int loadTexture(const char* a_pFileName, int & a_iWidth, int & a_iHeight, int a_iBPP);
	//can set up to 10 frames (0-9)
	void SetTexture(int frame, const char* textureName, int width, int height, int bpp);

	void Update();
	//set timer to zero by default. Goes up to 39 (0-39) so reset your clock after that
	void Draw(float timer);

};


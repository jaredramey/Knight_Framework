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

#pragma once

class Global
{
private:

public:
	//global variables & ect.
	GLFWwindow* window;

	Global();
	~Global();

	int wWidth = 1024, wHeight = 720;

	int Initialize();

	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
	GLuint CreateProgram(const char *a_vertex, const char *a_frag);
	float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);

};


//graphics libraries
#include <glew.h>
#include <wglew.h>
#include <glfw3.h>
#include "SOIL.h"
#include "glfont.h"
//default libraries
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
//custom headers/libraries
#include "Global.h"
#include "Knight_Quad.h"
#include "Knight_Triangle.h"


int main()
{
	//initialize glew and such
	Global init;
	init.Initialize();

	//trying to get glfont working
	//Initialize OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Initialize the viewport
	glViewport(0, 0, 1024, 720);

	//Initialize OpenGL projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 1024.0f, 720.0f, 0.0f, -2.0f, 2.0f);

	//Clear back buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Create font
	GLuint textureName;
	glGenTextures(1, &textureName);
	PixelPerfectGLFont font;
	try {
		font.Create("DatFont.glf", textureName);
	}
	catch (GLFontError::InvalidFile) {
		std::cerr << "Cannot load font\n";
		abort();
	}

	//Place to test classes
	Knight_Triangle* testTriangle = new Knight_Triangle();
	Knight_Quad* testQuad = new Knight_Quad[4];

	//Setting up the player to test the triangle
	testTriangle->InitTriangle();
	testTriangle->SetPosition(0, (1024 / 2.0), (720 / 2.0 + 100));
	testTriangle->SetPosition(1, (1024 / 2.0 - 100.0f), (720 / 2.0 - 100.0f));
	testTriangle->SetPosition(2,(1024 / 2.0 + 100.0f), (720 / 2.0 - 100.0f));

	testTriangle->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	testTriangle->SetUVs(0, 0.0f, 1.0f);
	testTriangle->SetUVs(1, 0.0f, 0.0f);
	testTriangle->SetUVs(2, 1.0f, 0.0f);

	int width = 50, heigth = 50, bpp = 4;
	testTriangle->SetTexture(0, "frame-1.png", width, heigth, bpp);
	testTriangle->SetTexture(1, "frame-2.png", width, heigth, bpp);
	testTriangle->SetTexture(2, "frame-3.png", width, heigth, bpp);
	testTriangle->SetTexture(3, "frame-4.png", width, heigth, bpp);
	testTriangle->SetTexture(4, "frame-5.png", width, heigth, bpp);
	testTriangle->SetTexture(5, "frame-6.png", width, heigth, bpp);
	testTriangle->SetTexture(6, "frame-7.png", width, heigth, bpp);
	testTriangle->SetTexture(7, "frame-8.png", width, heigth, bpp);


	//setting up test Quad
	testQuad[0].SetPosition(0, (1024 / 2.0 - 100.0f), (720 / 2.0));
	testQuad[1].SetPosition(1, (1024 / 2.0 - 100.0f), (720 / 2.0 - 100.0f));
	testQuad[2].SetPosition(2, (1024 / 2.0 + 100.0f), (720 / 2.0 - 100.0f));
	testQuad[3].SetPosition(3, (1024 / 2.0 + 100.0f), (720 / 2.0));

	testQuad[0].SetUVs(0, 0.0f, 1.0f);
	testQuad[1].SetUVs(1, 0.0f, 0.0f);
	testQuad[2].SetUVs(2, 1.0f, 0.0f);
	testQuad[3].SetUVs(3, 1.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//temporary place to create the buffers
	//create ID for a vertex buffer object
	//create shader program
	GLuint uiProgramFlat = init.CreateProgram("VertexShader.glsl", "FlatFragmentShader.glsl");
	GLuint uiProgramTextured = init.CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");

	//find the position of the matrix var in the shader so we can send info there later
	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "MVP");

	//set up the mapping of the screen to pixel co-ordinates. Try changing values and see what happens
	float *orthographicProjection = init.getOrtho(0, 1080, 0, 720, 0, 180);

	float timer = 0;

	while (!glfwWindowShouldClose(init.window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		system("CLS");
		//Draw some stuff
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glColor3f(1.0f, 1.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//send orthographic projection info to shader
		glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

		//glUseProgram(uiProgramFlat);
		glUseProgram(uiProgramTextured);

		//Main loop code goes here
		testTriangle->Draw(timer);

		timer += 3;
		std::cerr << timer << "\n";
		if (timer >= 30)
		{
			timer = 0;
		}

		glUseProgram(0);


		try {
			font.Begin();

			font.TextOutThing("hello my wonderfull world", 400, 200, 0);
			font.TextOutThing("Test", 50, 50, 0);

		}
		catch (GLFontError::InvalidFont) {
			std::cerr << "Trying to draw with an uninitialized font\n";
			abort();
		}

		glDisable(GL_TEXTURE_2D);

		//swap front and back buffers
		glfwSwapBuffers(init.window);

		//poll for and process events
		glfwPollEvents();
	}

	//Code for deleting any buffers
	//delete the index buffer to free up allocated memory
	glLoadIdentity();

	glfwTerminate();
	return 0;
}
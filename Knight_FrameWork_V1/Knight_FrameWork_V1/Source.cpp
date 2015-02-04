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
//custom headers/libraries
#include "Global.h"
#include "Knight_Quad.h"
#include "Knight_Triangle.h"
#include "TextHandler.h"


int main()
{
	//initialize glew and such
	Global init;
	init.Initialize();

	//class for texture handling
	TextHandler myText;

	//setting up text
	myText.SetFont("DaFont.fnt");

	//Place to test classes
	Knight_Triangle* testTriangle = new Knight_Triangle();
	Knight_Quad* testQuad = new Knight_Quad();


	//Setting up the player to test the triangle
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
	testQuad->SetPosition(0, (500.0f), (400.0f));
	testQuad->SetPosition(1, (500.0f), (300.0f));
	testQuad->SetPosition(2, (400.0f), (300.0f));
	testQuad->SetPosition(3, (400.0f), (400.0f));

	testQuad->SetColor(0, 1.0f, 1.0f, 1.0f, 1.0f);
	testQuad->SetColor(1, 1.0f, 1.0f, 1.0f, 1.0f);
	testQuad->SetColor(2, 1.0f, 1.0f, 1.0f, 1.0f);
	testQuad->SetColor(3, 1.0f, 1.0f, 1.0f, 1.0f);

	testQuad->SetUVs(0, 0.0f, 1.0f);
	testQuad->SetUVs(1, 0.0f, 0.0f);
	testQuad->SetUVs(2, 1.0f, 0.0f);
	testQuad->SetUVs(3, 1.0f, 1.0f);

	int widthS = 50, heigthS = 50, bppS = 4;
	testQuad->SetTexture(0, "frame-1.png", widthS, heigthS, bppS);
	testQuad->SetTexture(1, "frame-2.png", widthS, heigthS, bppS);
	testQuad->SetTexture(2, "frame-3.png", widthS, heigthS, bppS);
	testQuad->SetTexture(3, "frame-4.png", widthS, heigthS, bppS);
	testQuad->SetTexture(4, "frame-5.png", widthS, heigthS, bppS);
	testQuad->SetTexture(5, "frame-6.png", widthS, heigthS, bppS);
	testQuad->SetTexture(6, "frame-7.png", widthS, heigthS, bppS);
	testQuad->SetTexture(7, "frame-8.png", widthS, heigthS, bppS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//temporary place to create the buffers
	//create ID for a vertex buffer object
	//create shader program
	GLuint uiProgramFlat = init.CreateProgram("VertexShader.glsl", "FlatFragmentShader.glsl");
	GLuint uiProgramTextured = init.CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");

	//find the position of the matrix var in the shader so we can send info there later
	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramTextured, "MVP");

	//set up the mapping of the screen to pixel co-ordinates. Try changing values and see what happens
	float *orthographicProjection = init.getOrtho(0, 1080, 0, 720, 0, 180);

	float timer = 0;

	while (!glfwWindowShouldClose(init.window))
	{
		system("CLS");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

		//send orthographic projection info to shader
		glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

		//glUseProgram(uiProgramFlat);
		glUseProgram(uiProgramTextured);

		//Main loop code goes here
		testTriangle->Draw(timer);
		testQuad->Draw(timer);

		//testing text
		myText.DrawString("@", 100, 100, 50, 50);

		timer += 3;
		std::cerr << timer << "\n";
		if (timer >= 30)
		{
			timer = 0;
		}


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
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
	myText.SetFont("DaFontV2.fnt");

	//Place to test classes
	Knight_Quad* testTriangle = new Knight_Quad();
	Knight_Quad* testQuad = new Knight_Quad();
	Knight_Quad* Egg = new Knight_Quad();

	//Variables for Egg (Ball)
	float bX = 512.0f, bY = 360;
	float bWidth = 50.0f, bHeigth = 75.0f;
	float bColor[4] = {1.0f, 1.0f, 1.0f, 1.0};
	//Creating the egg
	Egg->CreateQuad(bX, bY, bWidth, bHeigth, bColor, eLEFT);
	//Setting textures
	float etWidth = 128.0f, etHeigth = 128.0f, etBPP = 4;
	Egg->SetTexture(0, "egg1.png", etWidth, etHeigth, etBPP);
	Egg->SetTexture(1, "egg2.png", etWidth, etHeigth, etBPP);
	Egg->SetTexture(2, "egg3.png", etWidth, etHeigth, etBPP);
	Egg->SetTexture(3, "egg4.png", etWidth, etHeigth, etBPP);
	Egg->SetTexture(4, "egg5.png", etWidth, etHeigth, etBPP);
	Egg->SetTexture(5, "egg6.png", etWidth, etHeigth, etBPP);
	Egg->SetTexture(6, "egg7.png", etWidth, etHeigth, etBPP);


	//variables for testTriangle
	float tX = 1000, tY = 300;
	float tWidth = 75, tHeight = 100;
	float tColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//Setting up the player to test the triangle
	testTriangle->CreateQuad(tX, tY, tWidth, tHeight, tColor, eLEFT);

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
	//variables for testQuad
	float qX = 100, qY = 300;
	float qWidth = 75, qHeight = 100;
	float qColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	testQuad->CreateQuad(qX, qY, qWidth, qHeight, qColor, eRIGHT);

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

	//create shader program
	GLuint uiProgramFlat = init.CreateProgram("VertexShader.glsl", "FlatFragmentShader.glsl");
	GLuint uiProgramTextured = init.CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");

	//find the position of the matrix var in the shader so we can send info there later
	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramTextured, "MVP");

	//set up the mapping of the screen to pixel co-ordinates. Try changing values and see what happens
	float *orthographicProjection = init.getOrtho(0, 1080, 0, 720, 0, 180);

	float timer = 0;
	float ballTimer = 0;

	while (!glfwWindowShouldClose(init.window))
	{
		system("CLS");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		//send orthographic projection info to shader
		glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

		//glUseProgram(uiProgramFlat);
		glUseProgram(uiProgramTextured);

		//testing text
		myText.DrawString("Bird Pong", 400.0f, 650.0f, 20.0f, 30.0f);
		Egg->Draw(ballTimer);

		//Main loop code goes here
		testTriangle->Update(VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, 50.0f);
		testQuad->Update(0x57, 0x53, 0x41, 0x44, 50.0f);
		Egg->Move(eRIGHT, 30.0f);
		testQuad->Draw(timer);
		testTriangle->Draw(timer);

		timer += 6;
		std::cerr << timer << "\n";
		if (timer >= 30)
		{
			timer = 0;
		}

		ballTimer += 6;
		std::cerr << timer << "\n";
		if (ballTimer >= 26)
		{
			ballTimer = 0;
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
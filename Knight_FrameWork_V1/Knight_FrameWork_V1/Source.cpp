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
#include "Knight_Quad.h"
#include "Knight_Triangle.h"

//function prototypes
GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
GLuint CreateProgram(const char *a_vertex, const char *a_frag);
float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);
//unsigned int loadTexture(const char* a_pFileName, int & a_iWidth, int & a_iHeight, int a_iBPP);

int main()
{
	//Initialise GLFW
	if (!glfwInit())
	{
		return -1;
	}

	//create a windowed mode window and it's OpenGL context
	GLFWwindow* window;
	window = glfwCreateWindow(1024, 720, "Knight_FrameWork_v1", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//make the window's context current
	glfwMakeContextCurrent(window);

	//Initialize Glew
	if (glewInit() != GLEW_OK)
	{
		// OpenGL didn't start-up! shutdown GLFW and return an error code
		glfwTerminate();
		return -1;
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
	GLuint uiProgramFlat = CreateProgram("VertexShader.glsl", "FlatFragmentShader.glsl");
	GLuint uiProgramTextured = CreateProgram("VertexShader.glsl", "TexturedFragmentShader.glsl");

	//find the position of the matrix var in the shader so we can send info there later
	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "MVP");

	//set up the mapping of the screen to pixel co-ordinates. Try changing values and see what happens
	float *orthographicProjection = getOrtho(0, 1080, 0, 720, 0, 180);

	float timer = 0;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		system("CLS");

		//send orthographic projection info to shader
		glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

		//glUseProgram(uiProgramFlat);
		glUseProgram(uiProgramTextured);

		//Main loop code goes here
		testTriangle->Draw(timer);
		

		timer += 3;
		std::cerr << timer << "\n";
		if (timer >= 34)
		{
			timer = 0;
		}

		//Switch to default shader as to avoid any issues
		//glUseProgram(0);

		//swap front and back buffers
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}

	//Code for deleting any buffers
	//delete the index buffer to free up allocated memory

	glfwTerminate();
	return 0;
}

//functions fleshed out
GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile)
{
	std::string strShaderCode;
	//open shader file
	std::ifstream shaderStream(a_strShaderFile);
	//if that worked ok, load file line by line
	if (shaderStream.is_open())
	{
		std::string Line = "";
		while (std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();

	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);
	//load source code
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);
	if (iStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (a_eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return uiShader;
}

GLuint CreateProgram(const char *a_vertex, const char *a_frag)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}

float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	//to correspond with mat4 in the shader
	//ideally this function would be part of your matrix class
	//however I wasn't willing to write your matrix class for you just to show you this
	//so here we are in array format!
	//add this to your matrix class as a challenge if you like!
	float* toReturn = new float[12];
	toReturn[0] = 2.0 / (right - left);;
	toReturn[1] = toReturn[2] = toReturn[3] = toReturn[4] = 0;
	toReturn[5] = 2.0 / (top - bottom);
	toReturn[6] = toReturn[7] = toReturn[8] = toReturn[9] = 0;
	toReturn[10] = 2.0 / (a_fFar - a_fNear);
	toReturn[11] = 0;
	toReturn[12] = -1 * ((right + left) / (right - left));
	toReturn[13] = -1 * ((top + bottom) / (top - bottom));
	toReturn[14] = -1 * ((a_fFar + a_fNear) / (a_fFar - a_fNear));
	toReturn[15] = 1;
	return toReturn;
}

/*unsigned int loadTexture(const char* a_pFileName, int & a_iWidth, int & a_iHeight, int a_iBPP)
{
	unsigned int uiTextureID = 0;
	//check if the file exists
	if (a_pFileName != nullptr)
	{
		//read in image data from file
		unsigned char* pImageData = SOIL_load_image(a_pFileName, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_AUTO);

		//check for a successful read
		if (pImageData)
		{
			//create openGL texture handle
			uiTextureID = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

			//clear what was read in from file now that it's stored in the handle
			SOIL_free_image_data(pImageData);
		}

		//check for errors
		if (uiTextureID == 0)
		{
			std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
		}
		return uiTextureID;
	}
}*/

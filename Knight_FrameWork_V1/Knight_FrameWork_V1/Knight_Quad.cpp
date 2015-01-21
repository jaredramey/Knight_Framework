#include "Knight_Quad.h"


Knight_Quad::Knight_Quad()
{
}


Knight_Quad::~Knight_Quad()
{
}

void Knight_Quad::SetPosition(int point, float x, float y)
{
	if (point < 4 && point > -1)
	{
		points[point].fPositions[0] = x;
		points[point].fPositions[1] = y;
		points[point].fPositions[2] = 0.0f;
		points[point].fPositions[3] = 1.0f;
	}

}

void Knight_Quad::SetColor(float R, float G, float B, float Op)
{
	for (int i = 0; i < 4; i++)
	{
		points[i].fColours[0] = R;
		points[i].fColours[1] = G;
		points[i].fColours[2] = B;
		points[i].fColours[3] = Op;
	}
}

void Knight_Quad::SetUVs(int point, float U, float V)
{
	if (point < 4 && point > -1)
	{
		points[point].fUVs[0] = U;
		points[point].fUVs[1] = V;
	}
}

unsigned int Knight_Quad::loadTexture(const char* a_pFileName, int & a_iWidth, int & a_iHeight, int a_iBPP)
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
}


void Knight_Quad::SetTexture(int frame, const char* textureName, int width, int height, int bpp)
{
	TextureFrames[frame] = loadTexture(textureName, width, height, bpp);

}

void Knight_Quad::Update()
{
	/*if (GetAsyncKeyState(0x57))
	{
	fPositions[1] += 10.0f;
	isMoving = true;
	}

	if (GetAsyncKeyState(0x53))
	{
	fPositions[1] -= 10.0f;
	isMoving = true;
	}

	if (GetAsyncKeyState(0x41))
	{
	fPositions[0] -= 10.0f;
	isMoving = true;
	}

	if (GetAsyncKeyState(0x44))
	{
	fPositions[0] += 10.0f;
	isMoving = true;
	}
	else
	{
	isMoving = false;
	}*/
}

void Knight_Quad::Draw(float timer)
{

	if (timer == 0 || timer == 1 || timer == 2 || timer == 3)
	{
		if (TextureFrames[0] != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, TextureFrames[0]);
		}

		else
		{
			std::cerr << "Error: No texture loaded/ could not load texture" << std::endl;
		}
	}

	else if (timer == 4 || timer == 5 || timer == 6 || timer == 7)
	{
		if (TextureFrames[1] != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, TextureFrames[1]);
		}

	}

	else if (timer == 8 || timer == 9 || timer == 10 || timer == 11)
	{
		if (TextureFrames[2] != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, TextureFrames[2]);
		}
	}

	else if (timer == 12 || timer == 13 || timer == 14 || timer == 15)
	{
		if (TextureFrames[3] != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, TextureFrames[3]);
		}
	}

	else if (timer == 16 || timer == 17 || timer == 18 || timer == 19)
	{
		if (TextureFrames[4] != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, TextureFrames[4]);
		}
	}

	else if (timer == 20 || timer == 21 || timer == 22 || timer == 23)
	{
		if (TextureFrames[5] != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, TextureFrames[5]);
		}
	}

	else if (timer == 24 || timer == 25 || timer == 26 || timer == 27)
	{
		if (TextureFrames[6] != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, TextureFrames[6]);
		}
	}

	else if (timer == 28 || timer == 29 || timer == 30 || timer == 31)
	{
		if (TextureFrames[7] != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, TextureFrames[7]);
		}
	}

	else if (timer == 32 || timer == 33 || timer == 34 || timer == 35)
	{
		if (TextureFrames[8] != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, TextureFrames[8]);
		}
	}

	else if (timer == 36 || timer == 37 || timer == 38 || timer == 39)
	{
		if (TextureFrames[9] != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, TextureFrames[9]);
		}
	}
}

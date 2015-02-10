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

void Knight_Quad::SetColor(int point, float R, float G, float B, float Op)
{
	
		points[point].fColours[0] = R;
		points[point].fColours[1] = G;
		points[point].fColours[2] = B;
		points[point].fColours[3] = Op;
	
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

void Knight_Quad::Update(int cU, int cD, int cL, int cR, float speed)
{
		if (GetAsyncKeyState(cU) && y < 720)
		{
			points[0].fPositions[1] += speed;
			points[1].fPositions[1] += speed;
			points[2].fPositions[1] += speed;
			points[3].fPositions[1] += speed;
			y += speed;
			isMoving = true;
		}

		if (GetAsyncKeyState(cD) && y > 0)
		{
			points[0].fPositions[1] -= speed;
			points[1].fPositions[1] -= speed;
			points[2].fPositions[1] -= speed;
			points[3].fPositions[1] -= speed;
			y -= speed;
			isMoving = true;
		}

		if (GetAsyncKeyState(cL))
		{
			points[0].fPositions[0] -= speed;
			points[1].fPositions[0] -= speed;
			points[2].fPositions[0] -= speed;
			points[3].fPositions[0] -= speed;
			x -= speed;
			isMoving = true;
		}

		if (GetAsyncKeyState(cR))
		{
			points[0].fPositions[0] += speed;
			points[1].fPositions[0] += speed;
			points[2].fPositions[0] += speed;
			points[3].fPositions[0] += speed;
			x += speed;
			isMoving = true;
		}
	if (isMoving == true)
	{
		isMoving = false;
	}
}

void Knight_Quad::Draw(float timer)
{
	if (isMoving == false)
	{
		glGenBuffers(1, &uiVBO);
		//check it succeeded
		if (uiVBO != 0)
		{
			//bind VBO
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			//allocate space for vertices on the graphics card
			glBufferData(GL_ARRAY_BUFFER, sizeof(PointQuad)* 4, NULL, GL_STATIC_DRAW);
			//get pointer to allocated space on the graphics card
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			//copy data to graphics card
			memcpy(vBuffer, points, sizeof(PointQuad)* 4);
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		isMoving = true;
	}

	//create ID for an index buffer object
	glGenBuffers(1, &uiIBO);

	if (uiIBO != 0)
	{
		//bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
		//allocate space for verticies on the graphics card
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our verticies
		//In this case, they are in sequintial order
		for (int i = 0; i < 4; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind buffer
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


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

	//enable the vertex array states
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(PointQuad), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(PointQuad), (void*)(sizeof(float)* 4));
	//now to worry about the UVs and send that info to the graphics card as well
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(PointQuad), (void*)(sizeof(float)* 8));

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDeleteBuffers(1, &uiIBO);
}

void Knight_Quad::CreateQuad(float x, float y, float width, float heigth, float color[4], Direction myDirection)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->heigth = heigth;

	SetPosition(0, (x - width), (y + (heigth)));
	SetPosition(1, (x - (width)), (y - (heigth)));
	SetPosition(2, (x + (width)), (y - (heigth)));
	SetPosition(3, (x + width), (y + heigth));

	SetColor(0, color[0], color[1], color[2], color[3]);
	SetColor(1, color[0], color[1], color[2], color[3]);
	SetColor(2, color[0], color[1], color[2], color[3]);
	SetColor(3, color[0], color[1], color[2], color[3]);
	if (myDirection == eRIGHT)
	{
		SetUVs(0, 0.0f, 1.0f);
		SetUVs(1, 0.0f, 0.0f);
		SetUVs(2, 1.0f, 0.0f);
		SetUVs(3, 1.0f, 1.0f);
	}
	else if (myDirection == eLEFT)
	{
		SetUVs(0, 1.0f, 1.0f);
		SetUVs(1, 1.0f, 0.0f);
		SetUVs(2, 0.0f, 0.0f);
		SetUVs(3, 0.0f, 1.0f);
	}
}

void Knight_Quad::WindowCollision()
{
	if (y > (720 - heigth) && y > (0 + heigth))
	{
		points[0].fPositions[1] -= 200.0f;
		points[1].fPositions[1] -= 200.0f;
		points[2].fPositions[1] -= 200.0f;
		points[3].fPositions[1] -= 200.0f;
		y -= 100.0f;
	}

	else if (y < (720 - heigth) && y < (0 + heigth))
	{
		points[0].fPositions[1] += 200.0f;
		points[1].fPositions[1] += 200.0f;
		points[2].fPositions[1] += 200.0f;
		points[3].fPositions[1] += 200.0f;
		y -= 100.0f;
	}
}

bool Knight_Quad::Collision(Knight_Quad *otherQuad)
{
	int radius1 = this->width;
	int radius2 = otherQuad->width;
	int dx = otherQuad->x - this->x;
	int dy = otherQuad->y - this->y;
	int radii = radius1 + radius2;
	if ((dx * dx) + (dy * dy) < radii * radii)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Knight_Quad::Move(Direction direction, float speed)
{
	if (direction == eRIGHT)
	{
		points[0].fPositions[0] += speed;
		points[1].fPositions[0] += speed;
		points[2].fPositions[0] += speed;
		points[3].fPositions[0] += speed;
		x += speed;
		if (x < 1024)
		{
			aDirection = eLEFT;
		}
	}

	if (direction == eLEFT)
	{
		points[0].fPositions[0] -= speed;
		points[1].fPositions[0] -= speed;
		points[2].fPositions[0] -= speed;
		points[3].fPositions[0] -= speed;
		x -= speed;
		if (x < 0)
		{
			aDirection = eRIGHT;
		}
	}
}

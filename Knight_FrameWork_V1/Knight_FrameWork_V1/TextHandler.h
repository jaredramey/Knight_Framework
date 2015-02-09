#pragma once
#include "tinyxml2.h"
#include "Knight_Quad.h"
#include <string>

using namespace tinyxml2;

struct Char
{
	Knight_Quad texture;
	std::string stringName;
	float width, heigth;
	float uPos, vPos;
	float xOffset, yOffset, xAdvance;

};

class TextHandler
{
public:
	TextHandler();
	~TextHandler();

	void SetFont(std::string fontName);
	Char GetChar(int in_char);

	void DrawString(std::string line, float x, float y, int width, int heigth);
private:
	std::string fontName;
	Knight_Quad fontTexture;
	XMLDocument fontInfo;
	Knight_Quad CreatedText;
};


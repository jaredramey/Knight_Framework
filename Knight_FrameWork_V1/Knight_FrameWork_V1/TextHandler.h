#pragma once
#include "tinyxml2.h"
#include "Knight_Quad.h"
#include <string>

struct Char
{
	Knight_Quad texture;
	std::string stringName;
	float width, heigth;
	float x0, y0, x1, y1;
	float offset;

};

class TextHandler
{
public:
	TextHandler();
	~TextHandler();

	void SetFont(std::string fontName);
	//Char GetChar(int in_char);
private:
	std::string fontName;
	Knight_Quad fontTexture;
	//XMLDocument fontInfo;
};


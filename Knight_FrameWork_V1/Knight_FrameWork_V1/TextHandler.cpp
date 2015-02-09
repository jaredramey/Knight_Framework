#include "TextHandler.h"

using namespace tinyxml2;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

TextHandler::TextHandler()
{
}


TextHandler::~TextHandler()
{
}

void TextHandler::SetFont(std::string in_fontName)
{
	fontName = in_fontName;
	if (fontInfo.LoadFile(in_fontName.c_str()) != XML_NO_ERROR)
	{
		throw "file not found";
	}

	XMLElement* textureElement = fontInfo.FirstChildElement("font")->FirstChildElement("pages")->FirstChildElement("page");
	const char* textureName = textureElement->Attribute("file");
	fontTexture.SetTexture(0, textureName, 0, 0, 0);
}

Char TextHandler::GetChar(int in_char)
{
	Char out;
	out.texture = fontTexture;
	XMLElement* element = fontInfo.FirstChildElement("font")->FirstChildElement("chars")->FirstChildElement("char");
	while (element->IntAttribute("id") != in_char && element->IntAttribute("id") <= 255)
	{
		element = element->NextSiblingElement();
	}
	
	out.width = element->IntAttribute("width") /256.0f;
	out.heigth = element->IntAttribute("height") /256.0f;
	out.uPos = element->IntAttribute("x") /256.0f;
	out.vPos = element->IntAttribute("y") /256.0f;
	out.xOffset = element->FloatAttribute("xoffset");
	out.yOffset = element->FloatAttribute("yoffset");
	out.xAdvance = element->FloatAttribute("xadvance");

	return out;
}

void TextHandler::DrawString(std::string line, float x, float y, int width, int heigth)
{
	//take in the string and break it down to a character array to read it easier
	const int length = line.length();
	float textTimer = 0;
	for (int i = 0; i < length; i++)
	{
		Char textToBeCreated = GetChar(line[i]);
		if (i < 255)
		{
				//set the font
				//textToBeCreated.stringName = "DaFont_0.png";
				//Create a quad to display the text
				//change string name of the font texture to a const char* to be able to set it on the quad
				const char* textureName = "DaFont_0.png";//textToBeCreated[i].stringName.c_str();
				//set the texture
				textToBeCreated.texture.SetTexture(0, textureName, width, heigth, 4);
				//set UVs for text quad
				//Text is upside right! Woot!
				textToBeCreated.texture.SetUVs(0, (textToBeCreated.uPos + textToBeCreated.width), (1 - (textToBeCreated.vPos)));
				textToBeCreated.texture.SetUVs(1, (textToBeCreated.uPos + textToBeCreated.width), (1 - (textToBeCreated.vPos + textToBeCreated.heigth)));
				textToBeCreated.texture.SetUVs(2, (textToBeCreated.uPos), (1 - (textToBeCreated.vPos + textToBeCreated.heigth)));
				textToBeCreated.texture.SetUVs(3, (textToBeCreated.uPos), (1 - (textToBeCreated.vPos)));

				//set text color (white)
				textToBeCreated.texture.SetColor(0, 1.0f, 1.0f, 1.0f, 1.0f);
				textToBeCreated.texture.SetColor(1, 1.0f, 1.0f, 1.0f, 1.0f);
				textToBeCreated.texture.SetColor(2, 1.0f, 1.0f, 1.0f, 1.0f);
				textToBeCreated.texture.SetColor(3, 1.0f, 1.0f, 1.0f, 1.0f);

				//set position on screen
				if (i == 0)
				{
					textToBeCreated.texture.SetPosition(0, (x + width), (y + heigth));
					textToBeCreated.texture.SetPosition(1, (x + width), (y - heigth));
					textToBeCreated.texture.SetPosition(2, (x - width), (y - heigth));
					textToBeCreated.texture.SetPosition(3, (x - width), (y + heigth));
				}
				else
				{
					textToBeCreated.texture.SetPosition(0, (((x / 2)*i) + width), (y + heigth));
					textToBeCreated.texture.SetPosition(1, (((x / 2)*i) + width), (y - heigth));
					textToBeCreated.texture.SetPosition(2, (((x / 2)*i) - width), (y - heigth));
					textToBeCreated.texture.SetPosition(3, (((x / 2)*i) - width), (y + heigth));
				}

				textToBeCreated.texture.Draw(textTimer);
		}
	}
}
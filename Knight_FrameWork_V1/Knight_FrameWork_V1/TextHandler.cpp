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
	/*fontName = in_fontName;
	if (fontInfo.LoadFile(in_fontName.c_str()) != XML_NO_ERROR)
	{
		throw "file not found";
	}

	XMLElement* textureElement = fontInfo.FirstChildElement("font")->FirstChildElement("pages")->FirstChildElement("page");
	const char* textureName = textureElement->Attribute("file");
	fontTexture.SetTexture(0, textureName, 0, 0, 0);*/
}

/*Char TextHandler::GetChar(int in_char)
{
	Char out;
	out.texture = fontTexture;
	XMLElement* element = fontInfo.FirstChildElement("font")->FirstChildElement("chars")->FirstChildElement("char");
	while (element->IntAttribute("id") != in_char && element->IntAttribute("id") <= 255)
	{
		element = element->NextSiblingElement();
	}
	
	
}*/
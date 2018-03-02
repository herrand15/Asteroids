#pragma once
#ifndef TEXTRENDERIZING_H_INCLUDED
#define TEXTRENDERIZING_H_INCLUDED
#include "IncludeSDL.hpp"
#include <string>

#include <iostream>

class TextRenderizing {

public:
	TextRenderizing();
	TTF_Font * m_font;
	int width;
	int height;
	bool Init();
	TextRenderizing(int width_, int height_);
	void RenderText(std::string message, SDL_Color color, float x, float y);
	unsigned int power_two_floor(unsigned int val);
	

};









#endif // !TEXTRENDERIZING_H_INCLUDED

#pragma once

#include <string>

#include "screen/gfx.h"
#include "screen/objects/object.h"

class TEXT: public OBJECT {
public:
	font *getFont();
	void setFont(font *fnt);
	unsigned int getSize();
	void setSize(unsigned int size);
	unsigned int getWrap();
	void setWrap(unsigned int wrap);
	std::string getText();
	void setText(std::string text);
	TEXT();
private:
	font *fnt;
	unsigned int size;
	unsigned int wrap;
	std::string text;
};
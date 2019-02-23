#pragma once

#include <string>

#include "screen/gfx.h"
#include "screen/objects/object.h"

class TEXT: public OBJECT {
public:
	font *getFont() const;
	void setFont(font *fnt);
	unsigned int getSize() const;
	void setSize(unsigned int size);
	unsigned int getWrap() const;
	void setWrap(unsigned int wrap);
	std::string getText() const;
	void setText(std::string text);
private:
	font *fnt;
	unsigned int size;
	unsigned int wrap;
	std::string text;
};
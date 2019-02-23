#include "screen/objects/text.h"

font *TEXT::getFont() {
	return fnt;
}

void TEXT::setFont(font *fnt) {
	this->fnt = fnt;
}

unsigned int TEXT::getSize()
{
	return size;
}

void TEXT::setSize(unsigned int size) {
	this->size = size;
}

unsigned int TEXT::getWrap() {
	return wrap;
}

void TEXT::setWrap(unsigned int wrap) {
	this->wrap = wrap;
}

std::string TEXT::getText() {
	return text;
}

void TEXT::setText(std::string text) {
	this->text = text;
}
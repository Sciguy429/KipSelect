#include "screen/objects/object.h"

std::string OBJECT::getId() {
	return id;
}

void OBJECT::setId(std::string id) {
	this->id = id;
}

bool OBJECT::getIsStatic() {
	return isStatic;
}

void OBJECT::setIsStatic(bool isStatic) {
	this->isStatic = isStatic;
}

unsigned int OBJECT::getPosX() {
	return posX;
}

void OBJECT::setPosX(unsigned int posX) {
	this->posX = posX;
}

unsigned int OBJECT::getPosY() {
	return posY;
}

void OBJECT::setPosY(unsigned int posY) {
	this->posY = posY;
}

bool OBJECT::getCentered() {
	return centered;
}

void OBJECT::setCentered(bool centered) {
	this->centered = centered;
}
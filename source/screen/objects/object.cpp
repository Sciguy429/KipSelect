#include "screen/objects/object.h"

unsigned int OBJECT::getType() {
	return type;
}

void OBJECT::setType(unsigned int type) {
	this->type = type;
}

std::string OBJECT::getId() const {
	return id;
}

void OBJECT::setId(std::string id) {
	this->id = id;
}

bool OBJECT::getIsStatic() const {
	return isStatic;
}

void OBJECT::setIsStatic(bool isStatic) {
	this->isStatic = isStatic;
}

unsigned int OBJECT::getPosX() const {
	return posX;
}

void OBJECT::setPosX(unsigned int posX) {
	this->posX = posX;
}

unsigned int OBJECT::getPosY() const {
	return posY;
}

void OBJECT::setPosY(unsigned int posY) {
	this->posY = posY;
}

bool OBJECT::getCentered() const {
	return centered;
}

void OBJECT::setCentered(bool centered) {
	this->centered = centered;
}

OBJECT::OBJECT() {
	setType(OBJECT_TYPE_GENERIC);
}
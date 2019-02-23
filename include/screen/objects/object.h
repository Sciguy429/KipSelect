#pragma once

#include <string>

class OBJECT {
public:
	std::string getId();
	void setId(std::string id);
	bool getIsStatic();
	void setIsStatic(bool isStatic);
	unsigned int getPosX();
	void setPosX(unsigned int posX);
	unsigned int getPosY();
	void setPosY(unsigned int posY);
	bool getCentered();
	void setCentered(bool centered);
private:
	std::string id;
	bool isStatic;
	unsigned int posX;
	unsigned int posY;
	bool centered;
};
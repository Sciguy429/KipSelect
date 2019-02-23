#pragma once

#include <string>

class OBJECT {
public:
	std::string getId() const;
	void setId(std::string id);
	bool getIsStatic() const;
	void setIsStatic(bool isStatic);
	unsigned int getPosX() const;
	void setPosX(unsigned int posX);
	unsigned int getPosY() const;
	void setPosY(unsigned int posY);
	bool getCentered() const;
	void setCentered(bool centered);
	virtual ~OBJECT() {};
private:
	std::string id;
	bool isStatic;
	unsigned int posX;
	unsigned int posY;
	bool centered;
};
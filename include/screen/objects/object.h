#pragma once

#include <string>

#define OBJECT_TYPE_GENERIC 0
#define OBJECT_TYPE_TEXT 1
#define OBJECT_TYPE_BLIT 2
//#define OBJECT_TYPE_LIST 3

#define CENTER_TYPE_TOP_LEFT 0
#define CENTER_TYPE_TOP_RIGHT 1
#define CENTER_TYPE_BOTTOM_LEFT 2
#define CENTER_TYPE_BOTTOM_RIGHT 3

class OBJECT {
public:
	unsigned int getType();
	void setType(unsigned int type);
	std::string getId() const;
	void setId(std::string id);
	bool getIsStatic() const;
	void setIsStatic(bool isStatic);
	unsigned int getPosX() const;
	void setPosX(unsigned int posX);
	unsigned int getPosY() const;
	void setPosY(unsigned int posY);
	unsigned int getCenterType() const;
	void setCenterType(unsigned int centerType);
	OBJECT();
	virtual ~OBJECT() {};
private:
	unsigned int type;
	std::string id;
	bool isStatic;
	unsigned int posX;
	unsigned int posY;
	unsigned int centerType;
};
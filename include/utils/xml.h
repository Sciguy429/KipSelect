#pragma once

class XML {
public:
	void resetNodePointer();
	void advanceNodePointer();
	void recallNodePointer();
	XML(const char *xmlFilePath);
	~XML();
private:
	xmlDocPtr xmlDoc;
	xmlNodePtr xmlCur;
};
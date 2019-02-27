#pragma once

#include <string>
#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/parser.h>

#define XMLCHAR_TO_CONSTCHAR(xC) (reinterpret_cast<const char *>(xC))

class XPATHRESULT {
public:
	unsigned int getNodeCount();
	xmlNodePtr *getNodePtr();
	XPATHRESULT(xmlXPathObjectPtr xPathObjPtr);
	~XPATHRESULT();
private:
	xmlXPathObjectPtr xPathObjPtr;
};

class XML {
public:
	XPATHRESULT evalXPathExp(const char *exp);
	std::string getKeyword(xmlNodePtr nodePtr);
	XML(const char *xmlFilePath);
	~XML();
private:
	xmlDocPtr xmlDoc;
	xmlNodePtr xmlCur;
};
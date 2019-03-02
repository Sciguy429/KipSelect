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
	XPATHRESULT(xmlDocPtr xmlDoc, xmlXPathObjectPtr xPathObjPtr);
	XPATHRESULT() {};
	~XPATHRESULT();
private:
	xmlXPathObjectPtr xPathObjPtr;
	xmlDocPtr xmlDoc;
};

class XML {
public:
	XPATHRESULT evalXPathExp(bool *success, const char *exp);
	XPATHRESULT evalXPathExpFromNode(bool *success, xmlNodePtr nodePtr, const char *exp);
	std::string getKeyword(xmlNodePtr nodePtr);
	XML(bool *success, const char *xmlFilePath);
	~XML();
private:
	xmlDocPtr xmlDoc;
	xmlNodePtr xmlCur;
};
#pragma once

#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/parser.h>

class XPATHRESULT {
public:
	XPATHRESULT(xmlXPathObjectPtr xPathObjPtr);
	~XPATHRESULT();
private:
	xmlXPathObjectPtr xPathObjPtr;
};

class XML {
public:
	XPATHRESULT evalXPathExp(xmlChar *exp);
	XML(const char *xmlFilePath);
	~XML();
private:
	xmlDocPtr xmlDoc;
	xmlNodePtr xmlCur;
};
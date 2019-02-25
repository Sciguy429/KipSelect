#pragma once

#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>

class XML {
public:
	XML(const char *xmlFilePath);
	~XML();
private:
	xmlDocPtr xmlDoc;
	xmlNodePtr xmlCur;
};
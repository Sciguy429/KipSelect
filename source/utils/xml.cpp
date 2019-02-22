#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>

#include "utils/xml.h"

void XML::resetNodePointer() {
	if (xmlDoc != NULL) {
		xmlCur = xmlDocGetRootElement(xmlDoc);
	}
}

void XML::advanceNodePointer() {
	if (xmlDoc != NULL) {
		xmlCur = xmlCur->children;
	}
}

void XML::recallNodePointer() {
	if (xmlDoc != NULL) {
		xmlCur = xmlCur->parent;
	}
}

XML::XML(const char *xmlFilePath) {
	xmlDoc = xmlParseFile(xmlFilePath);
	if (xmlDoc != NULL) {
		xmlCur = xmlDocGetRootElement(xmlDoc);
		if (xmlCur == NULL) {
			xmlFreeDoc(xmlDoc);
		}
	}
}

XML::~XML() {
	if (xmlDoc != NULL) {
		xmlFreeDoc(xmlDoc);
	}
}
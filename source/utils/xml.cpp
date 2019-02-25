#include "utils/xml.h"

XML::XML(const char *xmlFilePath) {
	xmlDoc = xmlParseFile(xmlFilePath);
	if (xmlDoc == NULL) {
		return;
	}
	xmlCur = xmlDocGetRootElement(xmlDoc);
}

XML::~XML() {
	xmlFreeDoc(xmlDoc);
}
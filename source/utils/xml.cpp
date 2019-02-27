#include "utils/xml.h"

//XPATHRESULT :: CLASS
unsigned int XPATHRESULT::getNodeCount() {
	return xPathObjPtr->nodesetval->nodeNr;
}

xmlNodePtr *XPATHRESULT::getNodePtr() {
	return xPathObjPtr->nodesetval->nodeTab;;
}

XPATHRESULT::XPATHRESULT(xmlXPathObjectPtr xPathObjPtr) {
	this->xPathObjPtr = xPathObjPtr;
}

XPATHRESULT::~XPATHRESULT() {
	xmlXPathFreeObject(xPathObjPtr);
}
//XPATHRESULT :: END
//XML :: CLASS
XPATHRESULT XML::evalXPathExp(xmlChar *exp) {
	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;
	context = xmlXPathNewContext(xmlDoc);
	if (context == NULL) {
		printf("XML -- Error Makeing New XPath Context\n");
		return NULL;
	}
	result = xmlXPathEvalExpression(exp, context);
	xmlXPathFreeContext(context);
	if (result == NULL) {
		printf("XML -- Error Evaluating XPath Expression\n");
		return NULL;
	}
	if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
		xmlXPathFreeObject(result);
		printf("XML -- XPath Expression Returned No Results\n");
		return NULL;
	}
	return XPATHRESULT(result);
}

const char *XML::getKeyword(xmlNodePtr nodePtr) {
	xmlChar *keyword;
	keyword = xmlNodeListGetString(xmlDoc, nodePtr->children, 1);
	const char *out = reinterpret_cast<const char *>(keyword);
	xmlFree(keyword);
	return out;
}

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
//XML :: END
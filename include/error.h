#pragma once

#include "string"

typedef struct {
	std::string header;
	std::string info;
} errorStructure;

void errorLoadAssets();

bool isErrorThrown();

void errorThrow(unsigned int errorType);

void errorDestroyAssets();
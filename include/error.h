#pragma once

typedef struct {
	const char *header;
	const char *info;
} errorStructure;

void errorLoadAssets();

bool isErrorThrown();

void errorThrow(unsigned int errorType, const char *errorInfo);

void errorDestroyAssets();
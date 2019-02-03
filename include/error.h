#pragma once

#define MKDIR_ERROR 0
#define RENAME_ERROR 1
#define OFSTREAM_ERROR 2
#define BCT_LOCATION_ERROR 3
#define CURL_GENERIC_ERROR 4
#define CURL_HTTP_RESPONSE_ERROR 5
#define XML_ERROR 6
#define SPL_INITILIZE_ERROR 7
#define SPL_CONFIGURATION_ERROR 8
#define PAYLOAD_NOT_FOUND_ERROR 9

typedef struct {
	const char *header;
	const char *info;
} errorStructure;

void errorLoadAssets();

bool isErrorThrown();

void errorThrow(unsigned int errorType, const char *errorInfo);

void errorDestroyAssets();
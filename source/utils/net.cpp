#include <sstream>
#include <curl/curl.h>

#include "net.h"
#include "error.h"

size_t writeFile(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

void netDownloadFile(const char *url, const char *path) {
	CURL *curl;
	FILE *file;
	CURLcode res;
	long httpCode = 0;
	curl = curl_easy_init();
	if (curl) {
		file = fopen(path, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Kip Select By Sciguy429");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFile);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
		res = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		if (res != CURLE_OK) {
			errorThrow(CURL_GENERIC_ERROR, path);
			return;
		}
		if (httpCode != 200) {
			std::ostringstream ss;
			ss << httpCode;
			errorThrow(CURL_HTTP_RESPONSE_ERROR, ss.str().c_str());
			return;
		}
		curl_easy_cleanup(curl);
		fclose(file);
	}
}
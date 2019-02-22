#pragma once

#include <string>
#include <vector>

typedef struct {
	uint32_t out_offset;
	uint32_t out_size;
	uint32_t compressed_size;
	uint32_t attribute;
} kip_section_header_t;

typedef struct {
	uint32_t magic;
	char name[0xC];
	uint64_t title_id;
	uint32_t process_category;
	uint8_t main_thread_priority;
	uint8_t default_core;
	uint8_t _0x1E;
	uint8_t flags;
	kip_section_header_t section_headers[6];
	uint32_t capabilities[0x20];
	unsigned char data[];
} kip1_header_t;

typedef struct {
	std::string name;
	kip1_header_t *header;
	bool enabled;
} kipItem;

class KIP {
public:
	void scanKIP();
	void setKIPItemEnabled(unsigned int kipId, bool enabled);
	bool getKIPItemEnabled(unsigned int kipId);
	unsigned int getKIPItemCount();
	//menuItem getKIPMenuItem(unsigned int kipId);
private:
	kip1_header_t *getKipHeader(const char *path);
	std::vector<kipItem> kipItems;
};
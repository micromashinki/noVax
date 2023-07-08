#include <vector>

#define SIZE_MEMORY 1000000

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <arpa/inet.h>
#endif

#pragma once

class Cmemory
{

protected:
	std::vector<uint8_t> memory;

public:

	Cmemory() : memory(SIZE_MEMORY + 5, 0) {
	}

    bool operator==(const Cmemory& other) const {
        bool res = memory == other.memory;
        return res;
    }

    std::vector<uint8_t>& getMemory() {
        return memory;
    }


	void get(uint32_t index, uint8_t& dat) { dat = memory[index]; return; };
	void get(uint32_t index, uint16_t& dat) {
		dat = memory[index];
		dat = dat << 8;
		dat += memory[index + 1];
		dat = ntohs(dat);
	};

	void get(uint32_t index, uint32_t& dat) {
		dat = memory[index];
		dat = dat << 8;
		dat += memory[index + 1];
		dat = dat << 8;
		dat += memory[index + 2];
		dat = dat << 8;
		dat += memory[index + 3];
		dat = ntohl(dat);

		return;
	};


	void set(uint32_t index, const uint8_t dat) { memory[index] = dat; };

	void set(uint32_t index, const uint16_t dat) {
		uint16_t tmp = htons(dat);
		memory[index] = tmp >> 8;
		memory[index + 1] = (uint8_t)tmp;
	};

	void set(uint32_t index, const uint32_t dat) {
		uint32_t tmp = htonl(dat);
		memory[index + 3] = (uint8_t)tmp;
		tmp = (uint32_t)tmp >> 8;
		memory[index + 2] = (uint8_t)tmp;
		tmp = (uint32_t)tmp >> 8;
		memory[index + 1] = (uint8_t)tmp;
		tmp = (uint32_t)tmp >> 8;
		memory[index] = (uint8_t)tmp;
	};

};


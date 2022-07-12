#include <vector>

#define MAX_SIZE 10000

#ifdef _WIN32
	#include <winsock.h>
	#pragma comment(lib, "ws2_32.lib")
#else
	#include <arpa/inet.h>
#endif

#pragma once

class Cmemory
{

protected:
	std::vector<uint8_t> memory;

public:
		 std::vector<uint8_t>& getMemory() {
		return memory;
	}

	Cmemory(): memory(MAX_SIZE + 5,0) {				
	}

	void get(unsigned int index, uint8_t& dat) { dat = memory[index]; return; };
	void get(unsigned int index, uint16_t& dat) { 
		dat = memory[index]; 
		dat = dat << 8; 
		dat += memory[index + 1];  
		dat = ntohs(dat);
	};

	void get(unsigned int index, uint32_t& dat) {
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


	void set(unsigned int index,const uint8_t dat) { memory[index] = dat; };

	void set(unsigned int index, const uint16_t dat) { 
		uint16_t tmp = htons(dat); 	
		memory[index] = tmp >> 8;	
		memory[index + 1] = (uint8_t)tmp; 
	};

	void set(unsigned int index,const uint32_t dat) { 
		uint32_t tmp = htonl(dat);
		memory[index + 3] = (uint8_t) tmp;
		tmp = (uint32_t)tmp >> 8;
		memory[index + 2] = (uint8_t) tmp;
		tmp = (uint32_t)tmp >> 8;
		memory[index + 1] = (uint8_t)tmp ;
		tmp = (uint32_t)tmp >> 8;
		memory[index] = (uint8_t)tmp;
	};
	

};


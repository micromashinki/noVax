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
	std::vector<uint8_t> mem;


public:
	Cmemory(): mem(MAX_SIZE + 5,0) {

		//test value 
		mem[0] = 0xA0;
		mem[1] = 0x51;
		mem[2] = 0x90;

		//mem[6] = 4;
		mem[7] = 0xC0;
		//mem[8] = 0xFF;
		mem[9] = 0x7;
		//mem[10] = 0x33;
				
	}

	void get(unsigned int index, uint8_t& dat) { dat = mem[index]; return; };
	void get(unsigned int index, uint16_t& dat) { 
		dat = mem[index]; 
		dat = dat << 8; 
		dat += mem[index + 1];  
		dat = ntohs(dat);
	};

	void get(unsigned int index, uint32_t& dat) {
		dat = mem[index];
		dat = dat << 8;
		dat += mem[index + 1];
		dat = dat << 8;
		dat += mem[index + 2];
		dat = dat << 8;
		dat += mem[index + 3];
		dat = ntohl(dat);

		return;
	};


	void set(unsigned int index,const uint8_t dat) { mem[index] = dat; };

	void set(unsigned int index, const uint16_t dat) { 
		uint16_t tmp = htons(dat); 	
		mem[index] = tmp >> 8;	
		mem[index + 1] = (uint8_t)tmp; 
	};

	void set(unsigned int index,const uint32_t dat) { 
		uint32_t tmp = htonl(dat);
		mem[index + 3] = (uint8_t) tmp;
		tmp = (uint32_t)tmp >> 8;
		mem[index + 2] = (uint8_t) tmp;
		tmp = (uint32_t)tmp >> 8;
		mem[index + 1] = (uint8_t)tmp ;
		tmp = (uint32_t)tmp >> 8;
		mem[index] = (uint8_t)tmp;
	};
	

};


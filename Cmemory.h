#include <vector>
#pragma once
#define MAX_SIZE 10000
class Cmemory
{

protected:
	std::vector<uint8_t> mem;


public:
	Cmemory(): mem(MAX_SIZE,0) {

		//test value 
		mem[0] = 0xA0;
		mem[1] = 0x51;
		mem[2] = 0x62;

		mem[6] = 4;
		mem[7] = 4;

		
	}

	void get(unsigned int index, uint8_t& dat) { dat = mem[index]; return; };
	void get(unsigned int index, uint16_t& dat) { dat = mem[index]; dat = dat << 8;	dat += mem[index + 1]; 	return; };
	//TODO: дописать это заглушка
	void get(unsigned int index, uint32_t& dat) { dat = mem[index]; return; };


	void set(unsigned int index,const uint8_t dat) { mem[index] = dat; };
	void set(unsigned int index,const uint16_t dat) { uint8_t tmp = dat >> 8; mem[index] = tmp;	mem[index + 1] = (uint8_t)dat;};
	//TODO: дописать, это заглушка
	void set(unsigned int index,const uint32_t dat) { uint8_t tmp = dat >> 8; mem[index] = dat; mem[index + 1] = tmp; };
	

};


#include "Cmemory.hpp"
#include <stdint.h>

#pragma once


class Cprocessor
{
public:
	Cprocessor() {
		//test value 
		registr[1] = 0xF;
		registr[2] = 7;

	}
	Cmemory memory;
	uint32_t registr[16];

			

	template<typename Type>
	Type get(uint32_t& index = *(registr + 15 * sizeof(registr[0]))) {
		uint8_t typeAdress;
		memory.get(index,typeAdress);
		

		auto h = typeAdress & 0x50;
		if (h == 0x50) {
			registr[15] += 1;
			return registr[typeAdress - 0x50];
		}

		h = typeAdress & 0x60;
		if (h == 0x60) {
			registr[15] += 1;
			Type dat;
			memory.get(registr[typeAdress - 0x60], dat);
			return dat;
		}
		
	}

	template<typename Type>
	void set(uint8_t index, const Type value) {
		uint8_t typeAdress;
		memory.get(index, typeAdress);

		auto h = typeAdress & 0x50;
		if (h == 0x50) {
			registr[15] += 1;
			registr[typeAdress - 0x50] = value;
		}

		h = typeAdress & 0x60;
		if (h == 0x60) {
			registr[15] += 1;
			memory.set(registr[typeAdress - 0x60], value);
		}

		
	}


	template<typename Type>
	void add2() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15]);
		set(registr[15] - 1, (Type)(op1 + op2));
	}


	void step() {
		uint8_t swit;
		memory.get(registr[15], swit);
		registr[15] += 1;

		switch (swit)
		{
		case 0x80:
			add2<uint8_t>();
			break;
		case 0xA0:
			add2<uint16_t>();
			break;
		case 0xC0:
			add2<uint32_t>();
			break;


		default:
			break;
		}

		return;
	}

};


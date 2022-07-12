#include "Cmemory.hpp"
#include <stdint.h>

#pragma once


class Cprocessor
{
public:
	Cprocessor() {
		//test value 
		registr[0] = 0x9;
		registr[1] = 0x60;

	}
	Cmemory memory;
	uint32_t registr[16];

			

	template<typename Type>
	Type get(uint32_t& index, bool finalOperation = true) {
		uint8_t typeAdress;
		memory.get(index,typeAdress);
		

		auto h = typeAdress & 0xF0;
		if (h == 0x50) {
			if(finalOperation)
				registr[15] += 1;
			return registr[typeAdress - 0x50];
		}

		if (h == 0x60) {
			if (finalOperation)
				registr[15] += 1;
			Type dat;
			memory.get(registr[typeAdress - 0x60], dat);
			return dat;
		}

		if (h == 0x70) {
			Type dat;
			if (finalOperation){
				registr[15] += 1;
				registr[typeAdress - 0x70] -= sizeof(Type);
			}
			memory.get(registr[typeAdress - 0x70], dat);
			return dat;
		}

		if (h == 0x80) {
			Type dat;
			memory.get(registr[typeAdress - 0x80], dat);
			if (finalOperation){
				registr[15] += 1;
				registr[typeAdress - 0x80] += sizeof(Type);
			}
			return dat;
		}

		if (h == 0x90) {
			Type dat;
			memory.get(registr[typeAdress - 0x90], dat);
			memory.get(dat, dat);
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x90] += sizeof(Type);
			}
			return dat;
		}


		
	}

	template<typename Type>
	void set(uint8_t index, const Type value, bool finalOperation = true) {
		uint8_t typeAdress;
		memory.get(index, typeAdress);

		auto h = typeAdress & 0xF0;
		if (h == 0x50) {
			if (finalOperation)
				registr[15] += 1;
			registr[typeAdress - 0x50] = value;
		}

		if (h == 0x60) {
			if (finalOperation)
				registr[15] += 1;
			memory.set(registr[typeAdress - 0x60], value);
		}

		if (h == 0x70) {
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x70] -= sizeof(Type);
			}
			memory.set(registr[typeAdress - 0x70], value);
		}

		if (h == 0x80) {
			memory.set(registr[typeAdress - 0x80], value);
			if (finalOperation) {
				registr[typeAdress - 0x80] += sizeof(Type);
				registr[15] += 1;
			}
			
		}

		if (h == 0x90) {
			Type dat;
			memory.get(registr[typeAdress - 0x90], dat);
			memory.set(dat, value);
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x90] += sizeof(Type);
			}
		}

		
	}


	template<typename Type>
	void add2() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15],false);
		set(registr[15], (Type)(op1 + op2));
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


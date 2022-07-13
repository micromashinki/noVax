#include "Cmemory.hpp"
#include <stdint.h>

#pragma once
class Cflags {
public:
	bool C { 0 };
	bool V{ 0 };
	bool Z{ 0 };
	bool N{ 0 };

	template<typename Type>
	void setFlags(Type value) {
		if (value == 0)
			Z = true;
		else 
			Z = false;

		if(value < (Type)MAXDWORD64)
			N = true;
		else
			N = false;
	}

};

class Cprocessor
{
	Cflags flag;
	Cmemory memory;
	std::vector<uint32_t> registr;


	template<typename Type>
	Type get(const uint32_t& index, bool finalOperation = true) {
		uint8_t typeAdress;
		memory.get(index, typeAdress);


		auto h = typeAdress & 0xF0;
		if (h == 0x50) {
			if (finalOperation)
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
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x70] -= sizeof(Type);
			}
			memory.get(registr[typeAdress - 0x70], dat);
			return dat;
		}

		if (h == 0x80) {
			Type dat;
			memory.get(registr[typeAdress - 0x80], dat);
			if (finalOperation) {
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
				registr[typeAdress - 0x90] += 4;
			}
			return dat;
		}
	}

	template<typename Type>
	void set(const uint32_t index, const Type value, bool finalOperation = true) {
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
				registr[typeAdress - 0x90] += 4;
			}
		}


	}


	template<typename Type>
	void add2() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15], false);
		flag.setFlags<Type>(op1 + op2);
		set(registr[15], (Type)(op1 + op2));
	}

	template<typename Type>
	void add3() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15]);
		flag.setFlags(op1 + op2);
		set(registr[15], (Type)(op1 + op2));
	}

	template<typename Type>
	void sub2() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15], false);
		flag.setFlags(op1 - op2);
		set(registr[15], (Type)(op1 - op2));
	}

	template<typename Type>
	void sub3() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15]);
		flag.setFlags(op1 - op2);
		set(registr[15], (Type)(op1 - op2));
	}

	template<typename Type>
	void inc() {
		Type op1 = get<Type>(registr[15], false);
		flag.setFlags(op1 + 1);
		set(registr[15], (Type)(op1 + 1));
	}

	template<typename Type>
	void dec() {
		Type op1 = get<Type>(registr[15], false);
		flag.setFlags(op1 - 1);
		set(registr[15], (Type)(op1 - 1));
	}

	template<typename Type>
	void mco() {
		Type op1 = get<Type>(registr[15]);
		flag.setFlags(~op1);
		set(registr[15], (Type)(~op1));
	}

	template<typename Type>
	void clr() {
		flag.setFlags(0);
		set(registr[15], (Type)(0));
	}

	template<typename Type>
	void bis() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15], false);
		flag.setFlags(op1 | op2);
		set(registr[15], (Type)(op1 | op2));
	}

	template<typename Type>
	void bic() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15], false);
		flag.setFlags(op1 & (~op2));
		set(registr[15], (Type)(op1 & (~op2)));
	}

	template<typename Type>
	void xor_() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15], false);
		flag.setFlags(op1 ^ op2);
		set(registr[15], (Type)(op1 ^ op2));
	}






public:
	Cprocessor() : registr(16, 0) {
	}

	const std::vector<uint8_t>& getMemory() {
		return memory.getMemory();
	}

	const std::vector<uint32_t>& getRegister() {
		return registr;
	}

	void setMemoryCell(const uint32_t index, const uint8_t value) {
		if (index <= MAX_SIZE)
			memory.set(index, (uint8_t)value);
	}

	void setRegisterCell(const uint8_t index, const uint32_t value) {
		if (index <= 16)
			registr[index] = value;
	}
	const Cflags& getFlags() {
		return flag;
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

		case 0x81:
			add3<uint8_t>();
			break;
		case 0xA1:
			add3<uint16_t>();
			break;
		case 0xC1:
			add3<uint32_t>();
			break;

		case 0x82:
			sub2<uint8_t>();
			break;
		case 0xA2:
			sub2<uint16_t>();
			break;
		case 0xC2:
			sub2<uint32_t>();
			break;

		case 0x83:
			sub3<uint8_t>();
			break;
		case 0xA3:
			sub3<uint16_t>();
			break;
		case 0xC3:
			sub3<uint32_t>();
			break;

		case 0x96:
			inc<uint8_t>();
			break;
		case 0xB6:
			inc<uint16_t>();
			break;
		case 0xD6:
			inc<uint32_t>();
			break;

		case 0x97:
			dec<uint8_t>();
			break;
		case 0xB7:
			dec<uint16_t>();
			break;
		case 0xD7:
			dec<uint32_t>();
			break;

		case 0x92:
			mco<uint8_t>();
			break;
		case 0xB2:
			mco<uint16_t>();
			break;
		case 0xD2:
			mco<uint32_t>();
			break;

		case 0x94:
			clr<uint8_t>();
			break;
		case 0xB4:
			clr<uint16_t>();
			break;
		case 0xD4:
			clr<uint32_t>();
			break;

		case 0x88:
			bis<uint8_t>();
			break;
		case 0xA8:
			bis<uint16_t>();
			break;
		case 0xC8:
			bis<uint32_t>();
			break;

		case 0x8A:
			bic<uint8_t>();
			break;
		case 0xAA:
			bic<uint16_t>();
			break;
		case 0xCA:
			bic<uint32_t>();
			break;

		case 0x8C:
			xor_<uint8_t>();
			break;
		case 0xAC:
			xor_<uint16_t>();
			break;
		case 0xCC:
			xor_<uint32_t>();
			break;

		default:
			break;
		}

		return;
	}

};


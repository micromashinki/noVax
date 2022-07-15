#include "Cmemory.hpp"
#include <stdint.h>
#include <string> 
#include <iostream>

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
		
		descriptionLastCommand.description += "get value: ";

		auto h = typeAdress & 0xF0;
		if (h == 0x50) {
			descriptionLastCommand.description += "5X adress R" + std::to_string(typeAdress - 0x50) + " value : " + std::to_string(registr[typeAdress - 0x50])+"\n";
			if (finalOperation)
				registr[15] += 1;
			return registr[typeAdress - 0x50];
		}

		if (h == 0x60) {
			if (finalOperation)
				registr[15] += 1;
			Type dat;
			memory.get(registr[typeAdress - 0x60], dat);
			descriptionLastCommand.description += "6X adress MEM" + std::to_string(registr[typeAdress - 0x60]) + " value : " + std::to_string(dat) + "\n";
			return dat;
		}

		if (h == 0x70) {
			Type dat;
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x70] -= sizeof(Type);
			}
			memory.get(registr[typeAdress - 0x70], dat);
			descriptionLastCommand.description += "7X adress MEM" + std::to_string(registr[typeAdress - 0x70]) + " value : " + std::to_string(dat) + "\n";
			return dat;
		}

		if (h == 0x80) {
			Type dat;
			memory.get(registr[typeAdress - 0x80], dat);
			descriptionLastCommand.description += "8X adress MEM" + std::to_string(registr[typeAdress - 0x80]) + " value : " + std::to_string(dat) + "\n";
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
			descriptionLastCommand.description += "9X adress MEM" + std::to_string(registr[typeAdress - 0x90]) + " value : " + std::to_string(dat) + "\n";
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x90] += 4;
			}
			return dat;
		}
		descriptionLastCommand.description += " unknown address";
		return 0;
	}

	template<typename Type>
	void set(const uint32_t index, const Type value, bool finalOperation = true) {
		uint8_t typeAdress;
		memory.get(index, typeAdress);

		auto h = typeAdress & 0xF0;
		descriptionLastCommand.description += "set value: ";
		if (h == 0x50) {
			if (finalOperation)
				registr[15] += 1;
			registr[typeAdress - 0x50] = value;
			descriptionLastCommand.description += "5X adress R" + std::to_string(typeAdress - 0x50) + " new value : " + std::to_string(registr[typeAdress - 0x50]) + "\n";
		}

		if (h == 0x60) {
			if (finalOperation)
				registr[15] += 1;
			memory.set(registr[typeAdress - 0x60], value);
			for (int i = 0; i < sizeof(Type); i++) { descriptionLastCommand.changeCell.push_back(registr[typeAdress - 0x60] + i); }
			
			Type dat;
			memory.get(registr[typeAdress - 0x60], dat);
			descriptionLastCommand.description += "6X adress MEM" + std::to_string(registr[typeAdress - 0x60]) + " new value : " + std::to_string(dat) + "\n";
		}

		if (h == 0x70) {
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x70] -= sizeof(Type);
			}
			memory.set(registr[typeAdress - 0x70], value);
			for (int i = 0; i < sizeof(Type); i++) { descriptionLastCommand.changeCell.push_back(registr[typeAdress - 0x70] + i); }

			Type dat;
			memory.get(registr[typeAdress - 0x70], dat);
			descriptionLastCommand.description += "7X adress MEM" + std::to_string(registr[typeAdress - 0x70]) + " new value : " + std::to_string(dat) + "\n";
		}

		if (h == 0x80) {
			memory.set(registr[typeAdress - 0x80], value);
			for (int i = 0; i < sizeof(Type); i++) { descriptionLastCommand.changeCell.push_back(registr[typeAdress - 0x80] + i); }
			Type dat;
			memory.get(registr[typeAdress - 0x80], dat);
			descriptionLastCommand.description += "8X adress MEM" + std::to_string(registr[typeAdress - 0x80]) + " new value : " + std::to_string(dat) + "\n";
			if (finalOperation) {
				registr[typeAdress - 0x80] += sizeof(Type);
				registr[15] += 1;
			}

		}

		if (h == 0x90) {
			Type dat;
			memory.get(registr[typeAdress - 0x90], dat);
			memory.set(dat, value);
			for (int i = 0; i < sizeof(Type); i++) { descriptionLastCommand.changeCell.push_back(dat + i); }
			memory.get(registr[typeAdress - 0x90], dat);
			memory.get(dat, dat);
			descriptionLastCommand.description += "9X adress MEM" + std::to_string(registr[typeAdress - 0x90]) + " new value : " + std::to_string(dat) + "\n";
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x90] += 4;
			}
		}

		descriptionLastCommand.description += " unknown address";
		return;

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
	

	struct SDescriptionLastCommand {
		std::vector<uint32_t> changeCell;
		std::string description;
	};
private:
	SDescriptionLastCommand descriptionLastCommand;
public:

	const SDescriptionLastCommand& getStepDescription(){
		return descriptionLastCommand;
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


	const SDescriptionLastCommand& step() {
		descriptionLastCommand.changeCell.clear();
		descriptionLastCommand.description.clear();
		uint8_t swit;
		memory.get(registr[15], swit);
		registr[15] += 1;


		descriptionLastCommand.description = "command: ";
		switch (swit)
		{
		case 0x80:
			descriptionLastCommand.description += std::to_string(swit)+'\n';
			add2<uint8_t>();
			break;
		case 0xA0:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			add2<uint16_t>();
			break;
		case 0xC0:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			add2<uint32_t>();
			break;

		case 0x81:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			add3<uint8_t>();
			break;
		case 0xA1:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			add3<uint16_t>();
			break;
		case 0xC1:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			add3<uint32_t>();
			break;

		case 0x82:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			sub2<uint8_t>();
			break;
		case 0xA2:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			sub2<uint16_t>();
			break;
		case 0xC2:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			sub2<uint32_t>();
			break;

		case 0x83:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			sub3<uint8_t>();
			break;
		case 0xA3:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			sub3<uint16_t>();
			break;
		case 0xC3:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			sub3<uint32_t>();
			break;

		case 0x96:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			inc<uint8_t>();
			break;
		case 0xB6:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			inc<uint16_t>();
			break;
		case 0xD6:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			inc<uint32_t>();
			break;

		case 0x97:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			dec<uint8_t>();
			break;
		case 0xB7:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			dec<uint16_t>();
			break;
		case 0xD7:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			dec<uint32_t>();
			break;

		case 0x92:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			mco<uint8_t>();
			break;
		case 0xB2:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			mco<uint16_t>();
			break;
		case 0xD2:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			mco<uint32_t>();
			break;

		case 0x94:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			clr<uint8_t>();
			break;
		case 0xB4:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			clr<uint16_t>();
			break;
		case 0xD4:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			clr<uint32_t>();
			break;

		case 0x88:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			bis<uint8_t>();
			break;
		case 0xA8:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			bis<uint16_t>();
			break;

		case 0xC8:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			bis<uint32_t>();
			break;

		case 0x8A:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			bic<uint8_t>();
			break;
		case 0xAA:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			bic<uint16_t>();
			break;
		case 0xCA:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			bic<uint32_t>();
			break;

		case 0x8C:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			xor_<uint8_t>();
			break;
		case 0xAC:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			xor_<uint16_t>();
			break;
		case 0xCC:
			descriptionLastCommand.description += std::to_string(swit) + '\n';
			xor_<uint32_t>();
			break;

		default:
			descriptionLastCommand.description += "unknown command" + '\n';
		}

		return descriptionLastCommand;
	}

};


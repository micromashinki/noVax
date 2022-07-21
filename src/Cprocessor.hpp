#pragma once
#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <string> 
#include <fstream>

#include "Cflags.h"
#include "Cmemory.hpp"
#include "ini-parser-master/ini.h"
#include "hex_printing.h"



class Cprocessor
{
	Cflags flag;
	Cmemory memory;
	std::vector<uint32_t> registr;

public:
	void load(const std::string& path) {
		IniFile file;
		file.open(path);
		auto section = file.get("Registers");
		auto end = section->get("dfghgfd");
		for (int i = 0; i < 16; i++)
			if (section->get("R" + int_to_hex(i)) != end)
				registr[i] = std::stoul(section->get("R" + int_to_hex(i))->second, 0, 16);

		section = file.get("Memory");
		end = section->get("dfghgfd");
		for (int i = 0; i < SIZE_MEMORY; i += 16) {
			if (section->get("0x"+int_to_hex_long_format(i)) != end) {
				std::string line = section->get("0x"+int_to_hex_long_format(i))->second;
				for (int j = 0; j < 16; j++) {
					auto ff = (uint8_t)std::stoul(line, 0, 16);
					memory.set(i + j, (uint8_t)std::stoul(line, 0, 16));

					if (line.length() > 3) {
						line.erase(0, 3);
					}

				}

			}
		}
	}
	void save(const std::string& path) {
		std::string file;
		file+="[Registers]\n";
		for (int i = 0; i < 16; i++) 
			if (registr[i] != 0)
				file += "R" + int_to_hex(i)+"=" + int_to_hex_long_format(registr[i])+"\n";


		file += "[Memory]\n";
		for (int i = 0; i < 10000; i += 16) {
			bool flag = false;
			uint8_t cell;
			for (int j = 0; j < 16; j++) {
				memory.get(i + j, cell);
				if (cell != 0)
					flag = true;
			}
			if (flag == true) {
				std::string arg;
				for (int j = 0; j < 16; j++,arg+=" ") {
					memory.get(i + j, cell);
					arg += int_to_hex_(cell);
				}
				file += "0x" + int_to_hex_long_format(i) +"="+arg + "\n";
			}
		}
		
		std::ofstream os(path);
		if (os) {
			os << file;
			os.close();
		}

	}
private:
	template<typename Type>
	Type get(const uint32_t& index, bool finalOperation = true) {
		uint8_t typeAdress;
		memory.get(index, typeAdress);

		descriptionLastCommand.description += "get value: ";

		auto h = typeAdress & 0xF0;
		if (h == 0x50) {
			descriptionLastCommand.description += "5X adress R" + std::to_string(typeAdress - 0x50) + " value : " + std::to_string(registr[typeAdress - 0x50]) + "\n";
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

		if (h == 0xA0) {
			uint8_t dat;
			Type data;
			memory.get(registr[typeAdress - 0xA0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xA0] + 2, data);

			if (finalOperation) {
				registr[typeAdress - 0xA0] += sizeof(dat) + 1;
			}
			return data;
		}

		if (h == 0xC0) {
			uint16_t dat;
			Type data;
			memory.get(registr[typeAdress - 0xC0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xC0] + 3, data);

			if (finalOperation) {
				registr[typeAdress - 0xC0] += sizeof(dat) + 1;
			}
			return data;
		}

		if (h == 0xE0) {
			uint32_t dat;
			Type data;
			memory.get(registr[typeAdress - 0xE0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xE0] + 5, data);

			if (finalOperation) {
				registr[typeAdress - 0xE0] += sizeof(dat) + 1;
			}
			return data;
		}

		if (h == 0xB0) {
			uint8_t dat;
			Type data;
			uint32_t adress;
			memory.get(registr[typeAdress - 0xB0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xB0] + 2, adress);
			memory.get(adress, data);

			if (finalOperation) {
				registr[typeAdress - 0xB0] += sizeof(dat) + 1;
			}
			return data;
		}

		if (h == 0xD0) {
			uint16_t dat;
			Type data;
			uint32_t adress;
			memory.get(registr[typeAdress - 0xD0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xD0] + 3, adress);
			memory.get(adress, data);

			if (finalOperation) {
				registr[typeAdress - 0xD0] += sizeof(dat) + 1;
			}
			return data;
		}

		if (h == 0xF0) {
			uint32_t dat;
			Type data;
			uint32_t adress;
			memory.get(registr[typeAdress - 0xF0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xF0] + 5, adress);
			memory.get(adress, data);

			if (finalOperation) {
				registr[typeAdress - 0xF0] += sizeof(dat) + 1;
			}
			return data;
		}

		descriptionLastCommand.description += " unknown address";
		return 0;
	}

	template<typename Type>
	void set(const uint32_t index, const Type value, bool finalOperation = true) {
		uint8_t typeAdress;
		memory.get(index, typeAdress);
		bool flag = false;
		auto h = typeAdress & 0xF0;
		descriptionLastCommand.description += "set value: ";

		if (h == 0x50) {
			if (finalOperation)
				registr[15] += 1;

			//registr[typeAdress - 0x50] = (uint32_t)value & (registr[typeAdress - 0x50] | ~registr[typeAdress - 0x50]);  //X2 ∧ (X1 ∨ !X1)
			registr[typeAdress - 0x50] = value;
			descriptionLastCommand.description += "5X adress R" + std::to_string(typeAdress - 0x50) + " new value : " + std::to_string(registr[typeAdress - 0x50]) + "\n";
			flag = true;
		}

		if (h == 0x60) {
			if (finalOperation)
				registr[15] += 1;
			memory.set(registr[typeAdress - 0x60], value);
			for (int i = 0; i < sizeof(Type); i++) { descriptionLastCommand.changeCell.push_back(registr[typeAdress - 0x60] + i); }

			Type dat;
			memory.get(registr[typeAdress - 0x60], dat);
			descriptionLastCommand.description += "6X adress MEM" + std::to_string(registr[typeAdress - 0x60]) + " new value : " + std::to_string(dat) + "\n";
			flag = true;
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
			flag = true;
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
			flag = true;
		}

		if (h == 0x90) {
			Type dat;
			uint32_t adress;
			memory.get(registr[typeAdress - 0x90], adress);
			memory.set(adress, value);
			for (int i = 0; i < sizeof(Type); i++) { descriptionLastCommand.changeCell.push_back(adress + i); }
			memory.get(registr[typeAdress - 0x90], dat);
			memory.get(dat, dat);
			descriptionLastCommand.description += "9X adress MEM" + std::to_string(registr[typeAdress - 0x90]) + " new value : " + std::to_string(dat) + "\n";
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x90] += 4;
			}
			flag = true;
		}

		if (h == 0xA0) {
			uint8_t dat;
			memory.get(registr[typeAdress - 0xA0] + 1, dat);
			memory.set(dat + registr[typeAdress - 0xA0] + 2, value);

			if (finalOperation) {
				registr[typeAdress - 0xA0] += sizeof(dat) + 1;
			}
			flag = true;
		}

		if (h == 0xC0) {
			uint16_t dat;
			memory.get(registr[typeAdress - 0xC0] + 1, dat);
			memory.set(dat + registr[typeAdress - 0xC0] + 3, value);

			if (finalOperation) {
				registr[typeAdress - 0xC0] += sizeof(dat) + 1;
			}
			flag = true;
		}

		if (h == 0xE0) {
			uint32_t dat;
			memory.get(registr[typeAdress - 0xE0] + 1, dat);
			memory.set(dat + registr[typeAdress - 0xE0] + 5, value);

			if (finalOperation) {
				registr[typeAdress - 0xE0] += sizeof(dat) + 1;
			}
			flag = true;
		}

		if (h == 0xB0) {
			uint8_t dat;
			Type data;
			uint32_t adress;
			memory.get(registr[typeAdress - 0xB0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xB0] + 2, adress);
			memory.set(adress, value);

			if (finalOperation) {
				registr[typeAdress - 0xB0] += sizeof(dat) + 1;
			}
			flag = true;
		}

		if (h == 0xD0) {
			uint16_t dat;
			Type data;
			uint32_t adress;
			memory.get(registr[typeAdress - 0xD0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xD0] + 3, adress);
			memory.set(adress, value);

			if (finalOperation) {
				registr[typeAdress - 0xD0] += sizeof(dat) + 1;
			}
			flag = true;
		}

		if (h == 0xF0) {
			uint32_t dat;
			Type data;
			uint32_t adress;
			memory.get(registr[typeAdress - 0xF0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xF0] + 5, adress);
			memory.set(adress, value);

			if (finalOperation) {
				registr[typeAdress - 0xF0] += sizeof(dat) + 1;
			}
			flag = true;
		}

		if (!flag)
			descriptionLastCommand.description += " unknown address";
		return;

	}
	template<typename Type>

	Type add(Type op1, Type op2, bool flagC = 0) {
		uint64_t result = (uint64_t)op1 + (uint64_t)op2 + (uint64_t)(flagC ? 1 : 0);
		int nBit = (sizeof(Type) * 8);
		uint64_t cMask = ((uint64_t)1 << nBit); // carry bit mask
		Type sMask = ((Type)1 << (nBit - 1));     // sign bit mask
		flag.C = ((result & cMask) != 0);
		flag.Z = (Type)result == 0;
		flag.N = (result & sMask) != 0;
		bool carryToSign = ((op1 ^ op2 ^ (Type)result) & sMask) != 0; // carry to sign bit
		flag.V = flag.C != carryToSign;
		//		bool flagV = flag.C != flag.N;
		return result;
	}

	template<typename Type>

	Type sub(Type op1, Type op2, bool flagC = 0) {
		uint64_t result = (uint64_t)op1 - (uint64_t)op2 - (uint64_t)(flagC ? 1 : 0);
		int nBit = (sizeof(Type) * 8);
		uint64_t cMask = ((uint64_t)1 << nBit); // carry bit mask
		Type sMask = ((Type)1 << (nBit - 1));     // sign bit mask
		flag.C = ((result & cMask) != 0);
		flag.Z = (Type)result == 0;
		flag.N = (result & sMask) != 0;
		bool carryToSign = ((op1 ^ op2 ^ (Type)result) & sMask) != 0; // carry to sign bit
		flag.V = flag.C != carryToSign;
		//		bool flagV = flag.C != flag.N;
		return result;
	}

	template<typename Type>
	void add2() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15], false);
		set(registr[15], (Type)add(op1, op2));
	}

	template<typename Type>
	void add3() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15]);
		set(registr[15], (Type)add(op1, op2));
	}

	template<typename Type>
	void sub2() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15], false);
		set(registr[15], (Type)(sub(op1, op2)));
	}

	template<typename Type>
	void sub3() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15]);
		set(registr[15], (Type)(sub(op1, op2)));
	}

	template<typename Type>
	void cmp() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15]);
		sub(op1, op2);
	}


	template<typename Type>
	void adwc() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15]);
		set(registr[15], (Type)(add(op1, op2, flag.C)));
	}
	template<typename Type>
	void sbwc() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15], false);
		set(registr[15], (Type)(sub(op1, op2, flag.C)));
	}

	template<typename Type>
	void inc() {
		Type op1 = get<Type>(registr[15], false);
		set(registr[15], add(op1, (Type)1));
	}

	template<typename Type>
	void dec() {
		Type op1 = get<Type>(registr[15], false);
		set(registr[15], sub(op1, (Type)1));
	}

	template<typename Type>
	void mne() {
		Type op1 = get<Type>(registr[15]);
		set(registr[15], (Type)(~op1 + 1));

		flag.V = 0;
		flag.Z = (~op1) == 0 ? 0 : 1;
		flag.N = (Type)MAXINT64 / 2 > op1 ? 1 : 0;

	}
	template<typename Type>
	void mco() {
		Type op1 = get<Type>(registr[15]);
		set(registr[15], (Type)(~op1));

		flag.V = 0;
		flag.Z = (~op1) == 0 ? 0 : 1;
		flag.N = (Type)MAXINT64 / 2 > op1 ? 1 : 0;

	}

	template<typename Type>
	void clr() {
		set(registr[15], (Type)(0));
		flag.V = 0;
		flag.Z = 1;
		flag.N = 0;
	}

	template<typename Type>
	void bis() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15], false);
		set(registr[15], (Type)(op1 | op2));
		flag.V = 0;
		flag.Z = (op1 | op2) == 0 ? 0 : 1;
		flag.N = (Type)MAXINT64 / 2 > (op1 | op2) ? 1 : 0;
	}

	template<typename Type>
	void bic() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15], false);
		set(registr[15], (Type)((~op2) & op1));
		flag.V = 0;
		flag.Z = ((~op2) & op1) == 0 ? 0 : 1;
		flag.N = (Type)MAXINT64 / 2 > (~op2) & op1 ? 1 : 0;
	}

	template<typename Type>
	void xor_() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15], false);
		set(registr[15], (Type)(op1 ^ op2));

		flag.V = 0;
		flag.Z = op1 ^ op2 == 0 ? 0 : 1;
		flag.N = (Type)MAXINT64 / 2 > op1 ^ op2 ? 1 : 0;
	}

	template<typename Type>
	void mov() {
		Type op1 = get<Type>(registr[15]);
		set(registr[15], (Type)op1);

		flag.V = 0;
		flag.Z = op1 == 0 ? 0 : 1;
		flag.N = (Type)MAXINT64 / 2 > op1 ? 1 : 0;
	}

	template<typename Type>
	void brbw() {
		Type op1;
		memory.get(registr[15], op1);
		registr[15] += op1 + sizeof(Type);
	}

	// говно решение, переделать 
	// быстрый фикс для презентации 
	template<typename Type>
	uint32_t getPhysicalAddress(const uint32_t& index, bool finalOperation = true) {
		uint8_t typeAdress;
		memory.get(index, typeAdress);

		descriptionLastCommand.description += "get value: ";

		auto h = typeAdress & 0xF0;

		if (h == 0x60) {
			if (finalOperation)
				registr[15] += 1;
			
			descriptionLastCommand.description += "6X adress MEM" + std::to_string(registr[typeAdress - 0x60]) + "\n";
			return registr[typeAdress - 0x60];
		}

		if (h == 0x70) {
			Type dat;
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x70] -= sizeof(Type);
			}
			descriptionLastCommand.description += "7X adress MEM" + std::to_string(registr[typeAdress - 0x70]) + "\n";
			return registr[typeAdress - 0x70];
		}

		if (h == 0x80) {
			auto res = registr[typeAdress - 0x80];
			descriptionLastCommand.description += "8X adress MEM" + std::to_string(registr[typeAdress - 0x80]) + "\n";
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x80] += sizeof(Type);
			}
			return res;
		}

		if (h == 0x90) {
			uint32_t res;
			memory.get(registr[typeAdress - 0x90], res);
			descriptionLastCommand.description += "9X adress MEM" + std::to_string(registr[typeAdress - 0x90]) + "\n";
			if (finalOperation) {
				registr[15] += 1;
				registr[typeAdress - 0x90] += 4;
			}
			return res;
		}

		if (h == 0xA0) {
			uint8_t dat;
			Type data;
			memory.get(registr[typeAdress - 0xA0] + 1, dat);
			uint32_t adress = dat + registr[typeAdress - 0xA0] + 2;

			if (finalOperation) {
				registr[typeAdress - 0xA0] += sizeof(dat) + 1;
			}
			return adress;
		}

		if (h == 0xC0) {
			uint16_t dat;
			Type data;
			memory.get(registr[typeAdress - 0xC0] + 1, dat);
			uint32_t adress = dat + registr[typeAdress - 0xC0] + 3;

			if (finalOperation) {
				registr[typeAdress - 0xC0] += sizeof(dat) + 1;
			}
			return adress;
		}

		if (h == 0xE0) {
			uint32_t dat;
			Type data;
			memory.get(registr[typeAdress - 0xE0] + 1, dat);
			uint32_t adress = dat + registr[typeAdress - 0xE0] + 5;

			if (finalOperation) {
				registr[typeAdress - 0xE0] += sizeof(dat) + 1;
			}
			return adress;
		}

		if (h == 0xB0) {
			uint8_t dat;
			Type data;
			uint32_t adress;
			memory.get(registr[typeAdress - 0xB0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xB0] + 2, adress);

			if (finalOperation) {
				registr[typeAdress - 0xB0] += sizeof(dat) + 1;
			}
			return adress;
		}

		if (h == 0xD0) {
			uint16_t dat;
			Type data;
			uint32_t adress;
			memory.get(registr[typeAdress - 0xD0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xD0] + 3, adress);

			if (finalOperation) {
				registr[typeAdress - 0xD0] += sizeof(dat) + 1;
			}
			return adress;
		}

		if (h == 0xF0) {
			uint32_t dat;
			Type data;
			uint32_t adress;
			memory.get(registr[typeAdress - 0xF0] + 1, dat);
			memory.get(dat + registr[typeAdress - 0xF0] + 5, adress);

			if (finalOperation) {
				registr[typeAdress - 0xF0] += sizeof(dat) + 1;
			}
			return adress;
		}

		descriptionLastCommand.description += " unknown address";
		return 0;
	}
	template<typename Type>
	void ash() {
		Type op1 = get<Type>(registr[15]);
		Type op2 = get<Type>(registr[15]);
		if ((Type)UINT64_MAX / 2 > op1) {
			set<Type>(op2 >> (op1 - (Type)UINT64_MAX / 2));
		}
		else {
			set<Type>(op2 << (op1 - (Type)UINT64_MAX / 2));
		}
		
	}

	template<typename Type>
	void jmp() {
		Type op1 = getPhysicalAddress<Type>(registr[15]);
		registr[15] = op1;
	}


	template<typename Type>
	void jsb() {
		registr[14] -= 4;
		set(registr[14], registr[15]);
		registr[15] = get<Type>(registr[15]);
	}
	template<typename Type>
	void rsb() {
		registr[15] = get<Type>(registr[14]);
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
	const SDescriptionLastCommand& getStepDescription() {
		return descriptionLastCommand;
	}
	const std::vector<uint8_t>& getMemory() {
		return memory.getMemory();
	}

	const std::vector<uint32_t>& getRegister() {
		return registr;
	}

	void setMemoryCell(const uint32_t index, const uint8_t value) {
		if (index <= SIZE_MEMORY)
			memory.set(index, (uint8_t)value);
	}

	void setRegisterCell(const uint8_t index, const uint32_t value) {
		if (index < 16)
			registr[index] = value;
	}


	const Cflags& getFlags() {
		return flag;
	}

	const bool getCFlag() {
		return flag.C;
	}

	const bool getNFlag() {
		return flag.N;
	}

	const bool getVFlag() {
		return flag.V;
	}

	const bool getZFlag() {
		return flag.Z;
	}


	const SDescriptionLastCommand& step() {
		descriptionLastCommand.changeCell.clear();
		descriptionLastCommand.description.clear();
		uint8_t mackCommand;
		memory.get(registr[15], mackCommand);
		registr[15] += 1;


		descriptionLastCommand.description = "adress command: " + std::to_string(registr[15] - 1) + "\ncommand: ";
		switch (mackCommand)
		{
		case 0x80:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			add2<uint8_t>();
			break;
		case 0xA0:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			add2<uint16_t>();
			break;
		case 0xC0:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			add2<uint32_t>();
			break;

		case 0x81:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			add3<uint8_t>();
			break;
		case 0xA1:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			add3<uint16_t>();
			break;
		case 0xC1:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			add3<uint32_t>();
			break;

		case 0x82:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			sub2<uint8_t>();
			break;
		case 0xA2:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			sub2<uint16_t>();
			break;
		case 0xC2:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			sub2<uint32_t>();
			break;

		case 0x83:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			sub3<uint8_t>();
			break;
		case 0xA3:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			sub3<uint16_t>();
			break;
		case 0xC3:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			sub3<uint32_t>();
			break;

		case 0x96:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			inc<uint8_t>();
			break;
		case 0xB6:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			inc<uint16_t>();
			break;
		case 0xD6:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			inc<uint32_t>();
			break;

		case 0x97:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			dec<uint8_t>();
			break;
		case 0xB7:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			dec<uint16_t>();
			break;
		case 0xD7:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			dec<uint32_t>();
			break;

		case 0x8E:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			mne<uint8_t>();
			break;
		case 0xAE:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			mne<uint16_t>();
			break;
		case 0xCE:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			mne<uint32_t>();
			break;

		case 0x92:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			mco<uint8_t>();
			break;
		case 0xB2:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			mco<uint16_t>();
			break;
		case 0xD2:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			mco<uint32_t>();
			break;


		case 0x78:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			mco<uint32_t>();
			break;



		case 0x94:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			clr<uint8_t>();
			break;
		case 0xB4:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			clr<uint16_t>();
			break;
		case 0xD4:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			clr<uint32_t>();
			break;

		case 0x88:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			bis<uint8_t>();
			break;
		case 0xA8:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			bis<uint16_t>();
			break;

		case 0xC8:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			bis<uint32_t>();
			break;

		case 0x8A:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			bic<uint8_t>();
			break;
		case 0xAA:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			bic<uint16_t>();
			break;
		case 0xCA:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			bic<uint32_t>();
			break;

		case 0x8C:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			xor_<uint8_t>();
			break;
		case 0xAC:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			xor_<uint16_t>();
			break;
		case 0xCC:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			xor_<uint32_t>();
			break;


		case 0x91:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			cmp<uint8_t>();
			break;
		case 0xB1:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			cmp<uint16_t>();
			break;
		case 0xD1:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			cmp<uint32_t>();
			break;


		case 0x90:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			mov<uint8_t>();
			break;
		case 0xB0:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			mov<uint16_t>();
			break;
		case 0xD0:
			descriptionLastCommand.description += std::to_string(mackCommand) + '\n';
			mov<uint32_t>();
			break;


		case 0x11:
			brbw<uint8_t>();
			break;

		case 0x31:
			brbw<uint16_t>();
			break;

		case 0x17:
			jmp<uint32_t>();
			break;

		case 0x16:
			jsb<uint32_t>();
			break;
		case 0x05:
			rsb<uint32_t>();
			break;

		case 0x14:
			if (flag.Z || (flag.N ^ flag.V) == 0) {
				uint32_t op1 = getPhysicalAddress<uint32_t>(registr[15]);
				registr[15] = op1;
			}
		default:
			descriptionLastCommand.description += " unknown command" + '\n';
		}

		return descriptionLastCommand;
	}

};
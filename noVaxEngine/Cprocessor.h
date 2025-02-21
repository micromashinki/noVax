﻿#pragma once

#include <iomanip>
#include <iostream>

#include <stdint.h>
#include <string>
#include <fstream>

#include "Cflags.h"
#include "Cmemory.hpp"
#include "../noVaxGUI/hex_printing.h"
#include <cstdint>
#include "inipp.h"


class Cprocessor {
    Cflags flag;
    Cmemory memory;
    std::vector<uint32_t> registr;

public:

    void clean() {
        flag = Cflags();
        memory = Cmemory();
        registr = std::vector<uint32_t>(16, 0);
    }

    Cprocessor() : registr(16, 0) {
    }

    struct SDescriptionLastCommand {
        std::vector<uint32_t> changeCell;
        std::string description;
    };

    bool operator==(const Cprocessor &other) const {
        return flag == other.flag && memory == other.memory && registr == other.registr;
    }

private:
    SDescriptionLastCommand descriptionLastCommand;
    std::vector<SDescriptionLastCommand> history;
public:

    void serFlags(bool N, bool Z, bool V, bool C) {
        flag.N = N;
        flag.Z = Z;
        flag.V = V;
        flag.C = C;
    }

    void load(const std::string &path);

    void save(const std::string &path);

private:


    template<typename Type>
    std::pair<Type,uint32_t > get_ValAddr(const uint32_t &index, bool finalOperation = true) {
        uint8_t typeAddress;
        memory.get(index, typeAddress);

        descriptionLastCommand.description += "get value: ";

        auto h = typeAddress & 0xF0;
        if (h == 0x50) {
            descriptionLastCommand.description += "5X address R" + int_to_hex(typeAddress - 0x50) + " value : " +
                                                  int_to_hex(registr[typeAddress - 0x50]) + "\n";
            if (finalOperation)
                registr[15] += 1;
            return {registr[typeAddress - 0x50], 0xffffffff};
        }

        if (h == 0x60) {
            uint32_t address;
            if (finalOperation)
                registr[15] += 1;
            Type dat;
            memory.get(address=registr[typeAddress - 0x60], dat);
            descriptionLastCommand.description +=
                    "6X address MEM" + int_to_hex(registr[typeAddress - 0x60]) + " value : " + int_to_hex(dat) + "\n";
            return {dat, address};
        }

        if (h == 0x70) {
            Type dat;
            uint32_t address;
            registr[15] += 1;

            auto saved_reg_val = registr[typeAddress - 0x70];
            registr[typeAddress - 0x70] -= sizeof(Type);

            memory.get(address=registr[typeAddress - 0x70], dat);
            descriptionLastCommand.description +=
                    "7X address MEM" + int_to_hex(registr[typeAddress - 0x70]) + " value : " + int_to_hex(dat) + "\n";

            if (!finalOperation) {
                registr[15] -= 1;
                registr[typeAddress - 0x70] = saved_reg_val;
            }
            return {dat, address};
        }

        if (h == 0x80) {
            Type dat;
            uint32_t address;
            memory.get(address=registr[typeAddress - 0x80], dat);
            descriptionLastCommand.description +=
                    "8X address MEM" + int_to_hex(registr[typeAddress - 0x80]) + " value : " + int_to_hex(dat) + "\n";
            if (finalOperation) {
                registr[15] += 1;
                registr[typeAddress - 0x80] += sizeof(Type);
            }
            return {dat,address};
        }

        if (h == 0x90) {
            Type dat;
            uint32_t address;
            memory.get(registr[typeAddress - 0x90], dat);
            memory.get(address=dat, dat);
            descriptionLastCommand.description +=
                    "9X address MEM" + int_to_hex(registr[typeAddress - 0x90]) + " value : " + int_to_hex(dat) + "\n";
            if (finalOperation) {
                registr[15] += 1;
                registr[typeAddress - 0x90] += 4;
            }
            return {dat, address};
        }

        if (h == 0xA0) {
            uint8_t offset;
            uint32_t address;
            Type dat;
            memory.get(registr[15] + 1, offset);
            memory.get(address=offset + registr[typeAddress - 0xA0], dat);
            descriptionLastCommand.description += "0xA0 new value : " + int_to_hex(dat) + "\n";
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }
            return {dat, address};
        }

        if (h == 0xC0) {
            uint16_t offset;
            uint32_t address;
            Type dat;
            memory.get(registr[15] + 1, offset);
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }
            memory.get(address = offset + registr[typeAddress - 0xC0], dat);
            descriptionLastCommand.description += "0xC0 new value : " + int_to_hex(dat) + "\n";

            return {dat, address};
        }

        if (h == 0xE0) {
            uint32_t offset;
            uint32_t address;
            Type dat;
            memory.get(registr[15] + 1, offset);
            memory.get(address=offset + registr[typeAddress - 0xE0], dat);
            descriptionLastCommand.description += "0xE0 new value : " + int_to_hex(dat) + "\n";
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }

            return {dat,address};
        }

        if (h == 0xB0) {
            uint8_t offset;
            Type data;
            uint32_t address;
            memory.get(registr[15] + 1, offset);
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }
            memory.get(offset + registr[typeAddress - 0xB0] , address);
            memory.get(address, data);
            descriptionLastCommand.description += "0xB0 new value : " + int_to_hex(data) +" from: "+ int_to_hex(address) +"\n";

            return {data,address};
        }

        if (h == 0xD0) {
            uint16_t offset;
            Type data;
            uint32_t address;
            memory.get(registr[15] + 1, offset);
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }
            memory.get(offset + registr[typeAddress - 0xD0], address);
            memory.get(address, data);
            descriptionLastCommand.description += "DX value : " + int_to_hex(data) +" from: "+ int_to_hex(address) +"\n";
            return {data,address};
        }

        if (h == 0xF0) {
            uint32_t offset;
            Type data;
            uint32_t address;
            memory.get(registr[15] + 1, offset);
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }
            memory.get(offset + registr[typeAddress - 0xF0], address);
            memory.get(address, data);
            descriptionLastCommand.description += "0xF0 value : " + int_to_hex(data) + "\n";

            return {data,address};
        }

        if (h == 0x40) {
            int code_index = index; // Разберись в set index значение, а в get - ссылка
            uint32_t offset;
            Type data;
            uint32_t address;
            if (finalOperation) {
                registr[15] += 1;
            }
            uint32_t array_index = registr[typeAddress - 0x40];
            std::cout << "array index: " << std::hex << array_index << std::endl;
            std::pair<Type,uint32_t > base = get_ValAddr<uint32_t>(code_index + 1, finalOperation);

            hexlog(base.second);
            hexlog(base.first);
            memory.get(address = (base.second + array_index * sizeof(Type)), data);
            descriptionLastCommand.description += "4X value : " + int_to_hex(data) + "\n";
            return {data,address};
        }

        if ((h &0xc0) == 0){ // если два старших бита кода алресации равны 0
            if (finalOperation) {
                registr[15] += + 1;
            }
            return {typeAddress& 0x3f,0xffffffff};   // 6 младших бит это литерал - вернем
        }

        descriptionLastCommand.description += " unknown address";
        return {0,0xffffffff};
    }

    void log(std::string a) {
        std::cout << a << std::endl;
    }

    template<typename Type>
    void hexlog(Type a) {
        std::cout << std::hex << a << std::endl;
    }

    template<typename Type>
    Type get(const uint32_t &index, bool finalOperation = true){
        return get_ValAddr<Type>( index, finalOperation).first;
    }

    template<typename Type>
    uint32_t getPhysicalAddress(const uint32_t &index, bool finalOperation = true) {
        return get_ValAddr<Type>( index, finalOperation).second;
    }


    template<typename Type>
    void set(const uint32_t index, const Type value, bool finalOperation = true) {
        uint8_t typeAddress;
        memory.get(index, typeAddress);
        bool flag = false;
        auto h = typeAddress & 0xF0;
        descriptionLastCommand.description += "set value: ";

        if (h == 0x50) {
            if (finalOperation)
                registr[15] += 1;

            int regno = typeAddress - 0x50;
            if (sizeof (Type)==1){
                registr[regno] &= 0xffffff00;
            }
            else if (sizeof (Type)==2){
                registr[regno] &= 0xffff0000;
            }
            else if (sizeof (Type)==4){
                registr[regno] = 0;
            }else{
                throw "Not implemented";
            }

            registr[typeAddress - 0x50] |= value;
            descriptionLastCommand.description += "5X address R" + int_to_hex(typeAddress - 0x50) + " new value : " +
                                                  int_to_hex(registr[typeAddress - 0x50]) + "\n";
            flag = true;
        }

        if (h == 0x60) {
            if (finalOperation)
                registr[15] += 1;
            memory.set(registr[typeAddress - 0x60], value);
            for (int i = 0; i < sizeof(Type); i++) {
                descriptionLastCommand.changeCell.push_back(registr[typeAddress - 0x60] + i);
            }

            Type dat;
            memory.get(registr[typeAddress - 0x60], dat);
            descriptionLastCommand.description +=
                    "6X address MEM" + int_to_hex(registr[typeAddress - 0x60]) + " new value : " + int_to_hex(dat) +
                    "\n";
            flag = true;
        }

        if (h == 0x70) {
            if (finalOperation) {
                registr[15] += 1;
                registr[typeAddress - 0x70] -= sizeof(Type);
            }
            memory.set(registr[typeAddress - 0x70], value);
            for (int i = 0; i < sizeof(Type); i++) {
                descriptionLastCommand.changeCell.push_back(registr[typeAddress - 0x70] + i);
            }

            Type dat;
            memory.get(registr[typeAddress - 0x70], dat);
            descriptionLastCommand.description +=
                    "7X address MEM" + int_to_hex(registr[typeAddress - 0x70]) + " new value : " + int_to_hex(dat) +
                    "\n";
            flag = true;
        }

        if (h == 0x80) {
            memory.set(registr[typeAddress - 0x80], value);
            for (int i = 0; i < sizeof(Type); i++) {
                descriptionLastCommand.changeCell.push_back(registr[typeAddress - 0x80] + i);
            }
            Type dat;
            memory.get(registr[typeAddress - 0x80], dat);
            descriptionLastCommand.description +=
                    "8X address MEM" + int_to_hex(registr[typeAddress - 0x80]) + " new value : " + int_to_hex(dat) +
                    "\n";
            if (finalOperation) {
                registr[typeAddress - 0x80] += sizeof(Type);
                registr[15] += 1;
            }
            flag = true;
        }

        if (h == 0x90) {
            Type dat;
            uint32_t address;
            memory.get(registr[typeAddress - 0x90], address);
            memory.set(address, value);
            for (int i = 0; i < sizeof(Type); i++) { descriptionLastCommand.changeCell.push_back(address + i); }
            memory.get(registr[typeAddress - 0x90], dat);
            memory.get(dat, dat);
            descriptionLastCommand.description +=
                    "9X address MEM" + int_to_hex(registr[typeAddress - 0x90]) + " new value : " + int_to_hex(dat) +
                    "\n";
            if (finalOperation) {
                registr[15] += 1;
                registr[typeAddress - 0x90] += 4;
            }
            flag = true;
        }

        if (h == 0xA0) {
            uint8_t offset;
            memory.get(registr[15] + 1, offset);
            memory.set(offset + registr[typeAddress - 0xA0], value);
            descriptionLastCommand.description += "0xA0 new value : " + int_to_hex(value) + "\n";
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }
            flag = true;
        }

        if (h == 0xC0) {
            uint16_t offset;
            memory.get(registr[15] + 1, offset);
            memory.set(offset + registr[typeAddress - 0xC0], value);
            descriptionLastCommand.description += "0xC0 new value : " + int_to_hex(value) + "\n";
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }
            flag = true;
        }

        if (h == 0xE0) {
            uint32_t offset;
            memory.get(registr[15] + 1, offset);
            memory.set(offset + registr[typeAddress - 0xE0], value);
            descriptionLastCommand.description += "0xE0 new value : " + int_to_hex(value) + "\n";
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }
            flag = true;
        }

        if (h == 0xB0) {
            uint8_t offset;
            Type data;
            uint32_t address;
            memory.get(registr[15] + 1, offset);
            memory.get(offset + registr[typeAddress - 0xB0], address);
            memory.set(address, value);
            descriptionLastCommand.description += "0xB0 new value : " + int_to_hex(value) + "\n";
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }
            flag = true;
        }

        if (h == 0xD0) {
            uint16_t offset;
            Type data;
            uint32_t address;
            memory.get(registr[15] + 1, offset);
            memory.get(offset + registr[typeAddress - 0xD0], address);
            memory.set(address, value);
            descriptionLastCommand.description += "0xD0 new value : " + int_to_hex(value) + "\n";
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }
            flag = true;
        }

        if (h == 0xF0) {
            uint32_t offset;
            Type data;
            uint32_t address;
            memory.get(registr[15] + 1, offset);
            memory.get(offset + registr[typeAddress - 0xF0], address);
            memory.set(address, value);
            descriptionLastCommand.description += "0xF0 new value : " + int_to_hex(value) + "\n";
            if (finalOperation) {
                registr[15] += sizeof(offset) + 1;
            }
            flag = true;
        }


        if (h == 0x40) {
            uint32_t offset;
            uint32_t address;
            if (finalOperation) {
                registr[15] += 1;
            }
            uint32_t iarr =registr[typeAddress - 0x40];
            std::pair<Type,uint32_t > base =  get_ValAddr <uint32_t>( index+1, finalOperation );


            memory.set(base.second+ iarr*sizeof(Type), value);
            descriptionLastCommand.description += "0x40 new value : " + int_to_hex(value) + "\n";
            flag = true;
        }


        if (!flag)
            descriptionLastCommand.description += " unknown address " + int_to_hex(typeAddress);
        return;

    }

public:
    template<typename Type>

    Type add(Type op1, Type op2, bool flagC = 0) {
        uint64_t result = (uint64_t) op1 + (uint64_t) op2 + (uint64_t) (flagC ? 1 : 0);
        int nBit = (sizeof(Type) * 8);
        uint64_t cMask = ((uint64_t) 1 << nBit); // carry bit mask
        Type sMask = ((Type) 1 << (nBit - 1));     // sign bit mask
        flag.C = ((result & cMask) != 0);
        flag.Z = (Type) result == 0;
        flag.N = (result & sMask) != 0;
        bool carryToSign = ((op1 ^ op2 ^ (Type) result) & sMask) != 0; // carry to sign bit
        flag.V = flag.C != carryToSign;
        //		bool flagV = flag.C != flag.N;
        return result;
    }

    template<typename Type>

    Type sub(Type op1, Type op2, bool flagC = 0) {
        uint64_t result = (uint64_t) op1 - (uint64_t) op2 - (uint64_t) (flagC ? 1 : 0);
        int nBit = (sizeof(Type) * 8);
        uint64_t cMask = ((uint64_t) 1 << nBit); // carry bit mask
        Type sMask = ((Type) 1 << (nBit - 1));     // sign bit mask
        flag.C = ((result & cMask) != 0);
        flag.Z = (Type) result == 0;
        flag.N = (result & sMask) != 0;
        bool carryToSign = ((op1 ^ op2 ^ (Type) result) & sMask) != 0; // carry to sign bit
        flag.V = flag.C != carryToSign;
        //		bool flagV = flag.C != flag.N;
        /*std::cout << std::hex << op1 << "\n";
        std::cout << std::hex << op2 << "\n";
        std::cout << std::hex << result << "\n";
        std::cout << flag.N << flag.Z << flag.V << flag.C;*/
        return result;
    }

    template<typename Type>
    void add2() {
        Type op1 = get<Type>(registr[15]);
        Type op2 = get<Type>(registr[15], false);
        set(registr[15], (Type) add(op1, op2));
    }

    template<typename Type>
    void add3() {
        Type op1 = get<Type>(registr[15]);
        Type op2 = get<Type>(registr[15]);
        set(registr[15], (Type) add(op1, op2));
    }

    template<typename Type>
    void sub2() {
        Type op1 = get<Type>(registr[15]);
        Type op2 = get<Type>(registr[15], false);
        set(registr[15], (Type) (sub(op2, op1)));
    }

    template<typename Type>
    void sub3() {
        Type op1 = get<Type>(registr[15]);
        Type op2 = get<Type>(registr[15]);
        set(registr[15], (Type) (sub(op2, op1)));
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
        Type op2 = get<Type>(registr[15], false);
        set(registr[15], (Type) (add(op1, op2, flag.C)));
    }

    template<typename Type>
    void sbwc() {
        Type op1 = get<Type>(registr[15]);
        Type op2 = get<Type>(registr[15], false);
        set(registr[15], (Type) (sub(op1, op2, flag.C)));
    }

    template<typename Type>
    void inc() {
        Type op1 = get<Type>(registr[15], false);
        set(registr[15], add(op1, (Type) 1));
    }

    template<typename Type>
    void dec() {
        Type op1 = get<Type>(registr[15], false);
        set(registr[15], sub(op1, (Type) 1));
    }

    template<typename Type>
    void mne() {
        Type op1 = get<Type>(registr[15]);
        set(registr[15], (Type) (~op1 + 1));

        flag.V = 0;
        flag.Z = (~op1) == 0 ? 1 : 0;
        flag.N = ((int64_t) ~op1 + 1) < 0 ? 1 : 0;

    }

    template<typename Type>
    void mco() {
        Type op1 = get<Type>(registr[15]);
        set(registr[15], (Type) (~op1));

        flag.V = 0;
        flag.Z = (~op1) == 0 ? 1 : 0;
        int nBit = (sizeof(Type) * 8);// carry bit mask
        Type sMask = ((Type) 1 << (nBit - 1));     // sign bit mask
        flag.N = ((~op1) & sMask) != 0;
//        std::cout << flag.N << flag.Z << flag.V << flag.C;
    }

    template<typename Type>
    void clr() {
        set(registr[15], (Type) (0));
        flag.V = 0;
        flag.Z = 1;
        flag.N = 0;
    }

    template<typename Type>
    void bis() {
        Type op1 = get<Type>(registr[15]);
        Type op2 = get<Type>(registr[15], false);
        set(registr[15], (Type) (op1 | op2));
        flag.V = 0;
        flag.Z = (op1 | op2) == 0 ? 1 : 0;
        flag.N = ((int64_t) op1 | op2) < 0 ? 1 : 0;
    }

    template<typename Type>
    void bic() {
        Type op1 = get<Type>(registr[15]);
        Type op2 = get<Type>(registr[15], false);
        set(registr[15], (Type) ((~op1) & op2));
//        std::cout << std::hex << ((~op1) & op1);
        flag.V = 0;
        flag.Z = ((~op2) & op1) == 0;
        int nBit = (sizeof(Type) * 8);// carry bit mask
        Type sMask = ((Type) 1 << (nBit - 1));     // sign bit mask
        flag.N = ((~op1) & sMask) != 0;
//        std::cout << flag.N << flag.Z << flag.V << flag.C;
    }

    template<typename Type>
    void xor_() {
        Type op1 = get<Type>(registr[15]);
        Type op2 = get<Type>(registr[15], false);
        set(registr[15], (Type) (op1 ^ op2));

        flag.V = 0;
        flag.Z = op1 ^ op2 == 0 ? 1 : 0;;
        flag.N = ((int64_t) op1 ^ op2) < 0 ? 1 : 0;
    }

    template<typename Type>
    void mov() {
        Type op1 = get<Type>(registr[15]);
        set(registr[15], (Type) op1);

        flag.V = 0;
        flag.Z = op1 == 0 ? 1 : 0;
        flag.N = ((int64_t) op1) < 0 ? 1 : 0;
    }

    template<typename Type>
    void brbw() {
        Type op1;
        memory.get(registr[15], op1);
        typedef typename std::make_signed<Type>::type T;
        registr[15] += (T) op1 + sizeof(Type);
    }

    template<typename Type>
    void acb() {
        Type op1 = get<Type>(registr[15]);
        Type op2 = get<Type>(registr[15]);
        Type op3 = get<Type>(registr[15], false);

        auto n = flag.N;
        auto z = flag.Z;
        auto v = flag.V;
        auto c = flag.C;

        auto op3value = (Type) add(op2, op3);

        flag.N = n;
        flag.Z = z;
        flag.V = v;
        flag.C = c;

        set(registr[15], op3value);

        typedef typename std::make_signed<Type>::type T;
        if (((T) op2 >= 0) && ((T) op3value <= (T) op1)) {
            brbw<uint16_t>();
        }
        else if (((T) op2 < 0) && ((T) op3value >= (T) op1)) {
            brbw<uint16_t>();
        }else {
            registr[15] += sizeof(uint16_t);
        }
    }

private:

    template<typename Type>
    void ash() {
        Type op1 = get<Type>(registr[15]);
        Type op2 = get<Type>(registr[15]);
        uint64_t tmp;
        if ((int64_t) op1 > 0) {
            tmp = op2 << op1;
        } else {
            tmp = op2 >> (~op1 + 1);
        }

        set<Type>(registr[15], (Type) tmp);

        flag.V = tmp >> (sizeof(Type) * 8 + 1);
        flag.C = 0;
        flag.Z = tmp == 0;
        flag.N = tmp < 0;
    }

    template<typename Type>
    void jmp() {
        Type op1 = getPhysicalAddress<Type>(registr[15]);
        registr[15] = op1;
    }


    template<typename Type>
    void jsb() {
        registr[14] -= 4;
        auto addr = get_ValAddr<Type>(registr[15]);
        memory.set(registr[14], registr[15]);
        registr[15] = addr.second;
    }

    template<typename Type>
    void rsb() {
        memory.get(registr[14], registr[15]);
        registr[14] += 4;
    }


public:
    const SDescriptionLastCommand &getStepDescription() {
        return descriptionLastCommand;
    }

    const std::vector<uint8_t> &getMemory() const {
        return memory.getMemory();
    }

    const std::vector<uint32_t> &getRegister() const {
        return registr;
    }

    void setMemoryCell(const uint32_t index, const uint8_t value) {
        if (index <= SIZE_MEMORY)
            memory.set(index, (uint8_t) value);
    }

    void setRegisterCell(const uint8_t index, const uint32_t value) {
        if (index < 16)
            registr[index] = value;
    }


    const Cflags &getFlags() const {
        return flag;
    }

    const bool getCFlag() const {
        return flag.C;
    }

    const bool getNFlag() const {
        return flag.N;
    }

    const bool getVFlag() const {
        return flag.V;
    }

    const bool getZFlag() const {
        return flag.Z;
    }


    const SDescriptionLastCommand &step() {
        descriptionLastCommand.changeCell.clear();
        descriptionLastCommand.description.clear();
        uint8_t mackCommand;
        memory.get(registr[15], mackCommand);
        registr[15] += 1;


        descriptionLastCommand.description = "address command: " + int_to_hex(registr[15] - 1) + "\ncommand: ";
        switch (mackCommand) {
            case 0x00:
                descriptionLastCommand.description = "HALT";
                break;

            case 0x80:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                add2<uint8_t>();
                break;
            case 0xA0:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                add2<uint16_t>();
                break;
            case 0xC0:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                add2<uint32_t>();
                break;

            case 0x81:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                add3<uint8_t>();
                break;
            case 0xA1:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                add3<uint16_t>();
                break;
            case 0xC1:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                add3<uint32_t>();
                break;

            case 0x82:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                sub2<uint8_t>();
                break;
            case 0xA2:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                sub2<uint16_t>();
                break;
            case 0xC2:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                sub2<uint32_t>();
                break;

            case 0x83:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                sub3<uint8_t>();
                break;
            case 0xA3:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                sub3<uint16_t>();
                break;
            case 0xC3:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                sub3<uint32_t>();
                break;

            case 0xD8:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                adwc<uint32_t>();
                break;

            case 0x96:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                inc<uint8_t>();
                break;
            case 0xB6:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                inc<uint16_t>();
                break;
            case 0xD6:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                inc<uint32_t>();
                break;

            case 0x97:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                dec<uint8_t>();
                break;
            case 0xB7:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                dec<uint16_t>();
                break;
            case 0xD7:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                dec<uint32_t>();
                break;

            case 0x8E:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                mne<uint8_t>();
                break;
            case 0xAE:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                mne<uint16_t>();
                break;
            case 0xCE:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                mne<uint32_t>();
                break;

            case 0x92:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                mco<uint8_t>();
                break;
            case 0xB2:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                mco<uint16_t>();
                break;
            case 0xD2:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                mco<uint32_t>();
                break;


            case 0x78:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                ash<uint32_t>();
                break;


            case 0x94:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                clr<uint8_t>();
                break;
            case 0xB4:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                clr<uint16_t>();
                break;
            case 0xD4:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                clr<uint32_t>();
                break;

            case 0x88:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                bis<uint8_t>();
                break;
            case 0xA8:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                bis<uint16_t>();
                break;

            case 0xC8:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                bis<uint32_t>();
                break;

            case 0x8A:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                bic<uint8_t>();
                break;
            case 0xAA:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                bic<uint16_t>();
                break;
            case 0xCA:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                bic<uint32_t>();
                break;

            case 0x8C:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                xor_<uint8_t>();
                break;
            case 0xAC:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                xor_<uint16_t>();
                break;
            case 0xCC:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                xor_<uint32_t>();
                break;


            case 0x91:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                cmp<uint8_t>();
                break;
            case 0xB1:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                cmp<uint16_t>();
                break;
            case 0xD1:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                cmp<uint32_t>();
                break;


            case 0x90:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                mov<uint8_t>();
                break;
            case 0xB0:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                mov<uint16_t>();
                break;
            case 0xD0:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                mov<uint32_t>();
                break;


            case 0x11:
                brbw<uint8_t>();
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                break;

            case 0x31:
                brbw<uint16_t>();
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                break;

            case 0x17:
                jmp<uint32_t>();
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                break;

            case 0x16:
                jsb<uint32_t>();
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                break;
            case 0x05:
                rsb<uint32_t>();
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                break;

            case 0x12:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if (flag.Z == 0) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x13:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if (flag.Z == 1) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x14:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if (flag.Z || (flag.N ^ flag.V) == 0) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x15:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if (flag.Z || (flag.N ^ flag.V) == 1) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x18:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if ((flag.N ^ flag.V) == 0) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x19:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if ((flag.N ^ flag.V) == 1) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x1A:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if ((flag.C || flag.Z) == 0) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x1B:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if ((flag.C || flag.Z) == 1) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x1C:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if (flag.V == 0) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x1D:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if (flag.V == 1) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x1E:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if (flag.C == 0) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x1F:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                if (flag.C == 1) {
                    brbw<uint8_t>();
                } else {
                    registr[15] += 1;
                }
                break;
            case 0x9D:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                acb<uint8_t>();
                break;
            case 0x3D:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                acb<uint16_t>();
                break;
            case 0xF1:
                descriptionLastCommand.description += int_to_hex(mackCommand) + '\n';
                acb<uint32_t>();
                break;
            default:
                descriptionLastCommand.description +=
                        std::string(" unknown command: ") + int_to_hex(mackCommand) + '\n';
        }


        return descriptionLastCommand;
    }

    std::vector<SDescriptionLastCommand> &execute() {
        history.clear();

        while (true) {
            auto desc = step();
            history.push_back(desc);
            std::cout << desc.description << std::endl;
            if (desc.description == "HALT") break;
        }
        std::cout << history.size();
        return history;
    }


};


::std::ostream &operator<<(::std::ostream &os, const Cprocessor &obj);

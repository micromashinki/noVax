//
// Created by chubr on 30.06.23.
//
#include <stdexcept>

#include "Cprocessor.h"

void Cprocessor::load(const std::string& path) {
    clean();
    inipp::Ini<char> ini;

    // read ini file
    std::ifstream is(path);
    if (!is) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    ini.parse(is);
    is.close();

    // Check if sections are present
    if (ini.sections.find("Registers") == ini.sections.end() ||
        ini.sections.find("Memory") == ini.sections.end()) {
        throw std::runtime_error("Missing required sections in ini file.");
    }

    // load registers
    auto &reg_section = ini.sections["Registers"];

    uint64_t PSL = 0; // Default value
    auto psl_it = reg_section.find("PSL");
    if (psl_it != reg_section.end()) {
        std::string pslStr = psl_it->second;
        try {
            PSL = std::stoul(pslStr, 0, 16);
        } catch (const std::invalid_argument& ia) {
            throw std::runtime_error("Invalid value for PSL register.");
        }
    }


    flag.C = PSL & 0x1;
    flag.V = (PSL >> 1) & 0x1;
    flag.Z = (PSL >> 2) & 0x1;
    flag.N = (PSL >> 3) & 0x1;


    for (int i = 0; i < 16; i++) {
        auto it = reg_section.find("R" + int_to_hex(i));
        if (it != reg_section.end()) {
            registr[i] = std::stoul(it->second, 0, 16);
        }
    }

    // load memory
    auto &mem_section = ini.sections["Memory"];
    for (int i = 0; i < SIZE_MEMORY; i += 16) {
        auto it = mem_section.find("0x" + int_to_hex_long_format(i));
        if (it != mem_section.end()) {
            std::string line = it->second;
            for (int j = 0; j < 16; j++) {
                if (line.length() >= 2) {
                    std::string byte_str = line.substr(0, 2);
                    memory.set(i + j, (uint8_t)std::stoul(byte_str, 0, 16));
                    if (line.length() > 2) {
                        line.erase(0, 3); // remove this byte and following space
                    }
                }
            }
        }
    }
}

void Cprocessor::save(const std::string& path) {
    inipp::Ini<char> ini;

    // populate the "Registers" section
    uint64_t PSL= (uint64_t)flag.C + ((uint64_t)flag.V << 1) + ((uint64_t)flag.Z << 2) + ((uint64_t)flag.N << 3);// flags
    ini.sections["Registers"]["PSL"]= int_to_hex_long_format(PSL);
    for (int i = 0; i < 16; i++) {
        if (registr[i] != 0) {
            ini.sections["Registers"]["R" + int_to_hex(i)] = int_to_hex_long_format(registr[i]);
        }
    }

    // populate the "Memory" section
    for (int i = 0; i < 10000; i += 16) {
        bool flag = false;
        uint8_t cell;
        std::string arg;
        for (int j = 0; j < 16; j++) {
            memory.get(i + j, cell);
            if (cell != 0) {
                flag = true;
            }
            if (j > 0) {
                arg += " ";
            }
            arg += int_to_hex_(cell);
        }
        if (flag) {
            ini.sections["Memory"]["0x" + int_to_hex_long_format(i)] = arg;
        }
    }


    std::ofstream os(path);
    if (os) {
        ini.generate(os);
        os.close();
    }

}


::std::ostream& operator<<(::std::ostream& os, const Cprocessor &proc) {
    auto r = proc.getRegister();
    auto l = proc.getFlags();

    os << "N: " << l.N << "  Z: " << l.Z << "  V: " << l.V << "  C: " << l.C<<std::endl;
    for (int i = 0; i < 16; i++)
        os << "R" << std::hex << i << std::setw(1) << "=" << std::setw(1) << std::hex <<(int)r[i]<< std::setw(3);

    os << std::endl << std::endl;

    auto m = proc.getMemory();
    os << ' ';

    for (int col = 0; col < 16; col++)
        os << 'M' << std::hex << col << std::setw((col + 9) % 16 == 0 ? 7:4);

    os << std::endl;


    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 16; col++) {
            std::stringstream ss;
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)m[col + row * 16];
            std::string result = ss.str();
            os << std::setw((col + row * 16 + 8) % 16 == 0 ? 8:5) << result;
        }
        os << std::endl;
    }


    os << std::endl << std::endl << std::endl;

    return os;
}

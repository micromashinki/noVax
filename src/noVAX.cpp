#include <iostream>
#include<iomanip>

#include "Cprocessor.hpp"

void drawProccessor(Cprocessor& processor) {
    auto g = processor.getStepDescription();
    std::cout << g.description<<std::endl;
    auto r = processor.getRegister();
    for (int i = 0; i < 16; i++)
        std::cout << "R" << std::hex << i << std::setw(1) << "=" << std::setw(1) << std::hex <<(int)r[i]<< std::setw(3);

    std::cout << std::endl << std::endl;

    auto m = processor.getMemory();
    std::cout << ' ' << ' ';

    for (int col = 0; col < 16; col++)
        std::cout << 'M' << std::hex << col << std::setw(col > 9 ? 3:4);

    std::cout << std::endl;
    std::cout << ' ' << ' ';

    for (int row = 15; row < 30; row++) {
        for (int col = 0; col < 16; col++)
            std::cout << std::hex << (int)m[col + row * 16] << (col + row * 16 - 1 > 1 ? (int)m[col + row * 16 - 1] <= 0xF ? std::setw(5) : std::setw(5) : std::setw(5));
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl << std::endl;

}

int main()
{
    Cprocessor pr;
    uint32_t ad = 0x118;
    pr.setMemoryCell(ad++, 0xA1);
    pr.setMemoryCell(ad++, 0x53);
    pr.setMemoryCell(ad++, 0x5A);
    pr.setMemoryCell(ad++, 0x6C);
    pr.setMemoryCell(ad++, 0xC0);
    pr.setMemoryCell(ad++, 0x5B);
    pr.setMemoryCell(ad++, 0x53);


    pr.setRegisterCell(0x2, 0xB2);
    pr.setRegisterCell(0x3, 0x2B);
    pr.setRegisterCell(0x4, 0xF42F);
    pr.setRegisterCell(0xA, 0x961);
    pr.setRegisterCell(0xB, 0x8BA0A1);
    pr.setRegisterCell(0xC, 0x33);
    pr.setRegisterCell(0xF, 0x118);


    drawProccessor(pr);
    pr.step();
    drawProccessor(pr);
    pr.step();
    drawProccessor(pr);
    pr.setMemoryCell(2, 0xB7);
    pr.setMemoryCell(3, 0x59);
    pr.step();
    drawProccessor(pr);
    
}


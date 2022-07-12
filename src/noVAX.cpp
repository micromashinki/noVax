#include <iostream>
#include<iomanip>

#include "Cprocessor.hpp"

void drawProccessor(Cprocessor& processor) {
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

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 16; col++)
            std::cout << std::hex << (int)m[col + row * 16] << (col + row * 16 - 1 > 1 ? (int)m[col + row * 16 - 1] <= 0xF ? std::setw(5) : std::setw(5) : std::setw(5));
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl << std::endl;

}

int main()
{
    Cprocessor pr;
    drawProccessor(pr);
    pr.setMemoryCell(0, 0xB6);//inc
    pr.setMemoryCell(1, 0x59);
    pr.step();
    drawProccessor(pr);

    pr.setRegisterCell(15, 0);//PC
    pr.step();
    drawProccessor(pr);

    pr.setMemoryCell(2, 0xB7);
    pr.setMemoryCell(3, 0x59);
    pr.step();
    drawProccessor(pr);
    
    
}


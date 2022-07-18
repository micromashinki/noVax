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

    for (int row = 0; row < 40; row++) {
        for (int col = 0; col < 16; col++)
            std::cout << std::hex << (int)m[col + row * 16] << (col + row * 16 - 1 > 1 ? (int)m[col + row * 16 - 1] <= 0xF ? std::setw(5) : std::setw(5) : std::setw(5));
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl << std::endl;

}

int main()
{
    Cprocessor pr;
    uint32_t ad = 0x0;
    pr.load("5.v11");
    //pr.setMemoryCell(ad++, 0xA0);
    //pr.setMemoryCell(ad++, 0x50);
    //pr.setMemoryCell(ad++, 0x51);

   // pr.setRegisterCell(0x0, 0xBBBBBBB);
   // pr.setRegisterCell(0x1, 0x1111111);


    drawProccessor(pr);
  //  pr.step();
   // drawProccessor(pr);

    
}


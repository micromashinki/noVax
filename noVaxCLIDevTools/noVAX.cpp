#include <iostream>
#include<iomanip>

#include "../noVaxEngine/Cprocessor.h"

inline void drawCprocessor(Cprocessor& processor) {
    std::cout << processor.getStepDescription().description<<std::endl << processor << std::endl;
}

int main()
{
    Cprocessor pr;
    uint32_t ad = 0x0;
    //pr.load("C:\\Users\\Chubr\\Desktop\\t2.v11");
    // pr.save("C:\\Users\\Chubr\\Desktop\\t3.v11");
    pr.setRegisterCell(0,0xAA);
    pr.setMemoryCell(ad++, 0x80);
    pr.setMemoryCell(ad++, 0x50);
    pr.setMemoryCell(ad++, 0x50);

    drawCprocessor(pr);    pr.step();
    pr.save("/home/chubr/Desktop/1234.v11");

    //pr.setMemoryCell(ad++, 0xA0);
    //pr.setMemoryCell(ad++, 0x50);
    //pr.setMemoryCell(ad++, 0x51);

   // pr.setRegisterCell(0x0, 0xBBBBBBB);
   // pr.setRegisterCell(0x1, 0x1111111);


    
  //  pr.step();
   // drawProccessor(pr);

    
}


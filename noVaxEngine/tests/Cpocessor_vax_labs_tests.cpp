//
// Created by misha on 14.07.2023.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include <cstdlib>

#define DEFAULT_PATH "../noVaxEngine/tests/file"
#define PATH_TEST DEFAULT_PATH "/Cprocessor_save_load/"

std::string getTestPath1() {
    const char* envPath = std::getenv("CPROCESSOR_TEST_PATH");
    return (envPath != nullptr) ? std::string(envPath) : std::string(PATH_TEST);
}

TEST(Cprocessor, lab1) {
    std::string path = getTestPath1();
    Cprocessor proc1;
    proc1.load(path + "1lab_do.v11");
    proc1.execute();

    Cprocessor proc2;
    proc2.load(path + "1lab_posle.v11");



    EXPECT_TRUE(proc1 == proc2);
}

TEST(Cprocessor, load_save_load_12) {
    std::string path = getTestPath1();
    Cprocessor proc1;
    Cprocessor proc2;
    proc1.load(path + "1.v11");
    proc1.save(path + "test_1.v11");
    proc2.load(path + "test_1.v11");
    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, load_22) {
    std::string path = getTestPath1();
    Cprocessor proc1;
    proc1.load(path + "2.v11");

    Cprocessor proc2;
    proc2.setMemoryCell(0x0,0x80);
    proc2.setMemoryCell(0x1,0x54);
    proc2.setMemoryCell(0x2,0x54);
    proc2.setMemoryCell(0x14E,0x56);
    proc2.setMemoryCell(0x14F,0x66);
    proc2.setRegisterCell(1,0x99);
    proc2.setRegisterCell(2,0x32);
    proc2.setRegisterCell(4,0x54);
    proc2.serFlags(0,1,1,1);

    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, load_save_load_22) {
    std::string path = getTestPath1();
    Cprocessor proc1;
    Cprocessor proc2;
    proc1.load(path + "2.v11");
    proc1.save(path + "test_2.v11");
    proc2.load(path + "test_2.v11");
    EXPECT_EQ(proc1,proc2);
}
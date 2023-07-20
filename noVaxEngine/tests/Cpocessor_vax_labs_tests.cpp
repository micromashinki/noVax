//
// Created by misha on 14.07.2023.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include "test.h"
#include <cstdlib>


TEST(Cprocessor, lab1) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_save_load "1lab_do.v11");
    proc1.execute();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_save_load"1lab_posle.v11");

    EXPECT_TRUE(proc1 == proc2);
}

TEST(Cprocessor, lab1_part_2) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_save_load "Lab_1_part_2_default.v11");
    proc1.execute();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_save_load"lab_1_part_2_after.v11");

    EXPECT_TRUE(proc1 == proc2);
}

TEST(Cprocessor, lab3_part_1) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_save_load "lab3_part_1_default.v11");
    proc1.execute();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_save_load"lab3_part_1_after.v11");

    EXPECT_TRUE(proc1 == proc2);
}

TEST(Cprocessor, lab3_part_2) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_save_load "lab3_part_2_default.v11");
    proc1.execute();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_save_load"lab3_part_2_after.v11");

    EXPECT_TRUE(proc1 == proc2);
}

TEST(Cprocessor, lab4) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_save_load "lab4_default.v11");
    proc1.execute();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_save_load"lab4_after.v11");

    EXPECT_TRUE(proc1 == proc2);
}
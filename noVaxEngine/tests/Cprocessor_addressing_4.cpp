//
// Created by chubr on 30.06.23.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include "test.h"





TEST(Cprocessor, byte_addressing_4) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_4 "byte.v11");
    proc1.step();
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_4 "byte_.v11");

    EXPECT_EQ(proc1,proc2);
}


TEST(Cprocessor, word_addressing_4) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_4 "word.v11");
    proc1.step();
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_4 "word_.v11");

    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, long_addressing_4) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_4 "long.v11");
    proc1.step();
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_4 "long_.v11");

    EXPECT_EQ(proc1,proc2);
}



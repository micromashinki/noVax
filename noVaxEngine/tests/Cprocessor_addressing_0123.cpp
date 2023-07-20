//
// Created by chubr on 30.06.23.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include "test.h"





TEST(Cprocessor, byte_addressing_0123) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_0123 "byte.v11");
    proc1.step();
    proc1.step();
    proc1.step();
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_0123 "byte_.v11");

    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, word_addressing_0123) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_0123 "word.v11");
    proc1.step();
    proc1.step();
    proc1.step();
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_0123 "word_.v11");

    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, long_addressing_0123) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_0123 "long.v11");
    proc1.step();
    proc1.step();
    proc1.step();
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_0123 "long_.v11");

    EXPECT_EQ(proc1,proc2);
}

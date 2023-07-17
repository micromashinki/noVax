//
// Created by chubr on 30.06.23.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include "test.h"





TEST(Cprocessor, byte_addressing_5) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_5 "byte.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_5 "_byte.v11");

    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, byte_addressing_5_3op) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_5 "byte_3op.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_5 "_byte_3op.v11");

    EXPECT_EQ(proc1,proc2);
}


TEST(Cprocessor, word_addressing_5) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_5 "word.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_5 "_word.v11");

    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, word_addressing_5_3op) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_5 "word_3op.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_5 "_word_3op.v11");

    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, long_addressing_5) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_5 "long.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_5 "_long.v11");

    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, long_addressing_5_3op) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_5 "long_3op.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_5 "_long_3op.v11");

    EXPECT_EQ(proc1,proc2);
}


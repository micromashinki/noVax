//
// Created by chubr on 10.07.23.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include "test.h"


TEST(Cprocessor, byte_addressing_6) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_6 "byte.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_6 "byte_.v11");

    EXPECT_EQ(proc1,proc2);
}


TEST(Cprocessor, byte_addressing_6_3op) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_6 "byte_3op.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_6 "byte_3op_.v11");

    EXPECT_EQ(proc1,proc2);
}


TEST(Cprocessor, word_addressing_6) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_6 "word.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_6 "word_.v11");

    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, word_addressing_6_3op) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_6 "word_3op.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_6 "word_3op_.v11");

    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, long_addressing_6) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_6 "long.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_6 "long_.v11");

    EXPECT_EQ(proc1,proc2);
}

TEST(Cprocessor, long_addressing_6_3op) {
    Cprocessor proc1;
    proc1.load(PATH_Cprocessor_addressing_6 "long_3op.v11");
    proc1.step();

    Cprocessor proc2;
    proc2.load(PATH_Cprocessor_addressing_6 "long_3op_.v11");

    EXPECT_EQ(proc1,proc2);
}

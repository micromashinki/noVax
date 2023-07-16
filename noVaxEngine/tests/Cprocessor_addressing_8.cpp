//
// Created by chubr on 16.07.23.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include "test.h"


TEST(Cprocessor, byte_addressing_8) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_8 "byte.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_8 "byte_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}


TEST(Cprocessor, byte_addressing_8_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_8 "byte_3op.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_8 "byte_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}


TEST(Cprocessor, word_addressing_8) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_8 "word.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_8 "word_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, word_addressing_8_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_8 "word_3op.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_8 "word_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, long_addressing_8) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_8 "long.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_8 "long_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, long_addressing_8_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_8 "long_3op.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_8 "long_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

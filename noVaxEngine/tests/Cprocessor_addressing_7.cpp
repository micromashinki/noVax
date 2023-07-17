//
// Created by chubr on 10.07.23.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include "test.h"


TEST(Cprocessor, byte_addressing_7) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_7 "byte.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_7 "byte_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}


TEST(Cprocessor, byte_addressing_7_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_7 "byte_3op.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_7 "byte_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}


TEST(Cprocessor, word_addressing_7) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_7 "word.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_7 "word_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, word_addressing_7_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_7 "word_3op.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_7 "word_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, long_addressing_7) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_7 "long.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_7 "long_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, long_addressing_7_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_7 "long_3op.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_7 "long_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

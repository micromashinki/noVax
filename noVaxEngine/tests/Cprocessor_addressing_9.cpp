//
// Created by chubr on 16.07.23.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include "test.h"


TEST(Cprocessor, byte_addressing_9) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_9 "byte.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_9 "byte_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}


TEST(Cprocessor, byte_addressing_9_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_9 "byte_3op.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_9 "byte_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}


TEST(Cprocessor, word_addressing_9) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_9 "word.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_9 "word_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, word_addressing_9_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_9 "word_3op.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_9 "word_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, long_addressing_9) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_9 "long.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_9 "long_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, long_addressing_9_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_9 "long_3op.v11");
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_9 "long_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

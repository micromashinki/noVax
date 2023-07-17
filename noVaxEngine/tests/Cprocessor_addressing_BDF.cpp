//
// Created by chubr on 18.07.23.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include "test.h"


TEST(Cprocessor, byte_addressing_BDF) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_BDF "byte.v11");
    noVaxProcessor.step();

    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_BDF "byte_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}


TEST(Cprocessor, byte_addressing_BDF_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_BDF "byte_3op.v11");
    noVaxProcessor.step();
    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_BDF "byte_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}


TEST(Cprocessor, word_addressing_BDF) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_BDF "word.v11");
    noVaxProcessor.step();
    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_BDF "word_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, word_addressing_BDF_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_BDF "word_3op.v11");
    noVaxProcessor.step();
    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_BDF "word_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, long_addressing_BDF) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_BDF "long.v11");
    noVaxProcessor.step();
    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_BDF "long_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, long_addressing_BDF_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_BDF "long_3op.v11");
    noVaxProcessor.step();
    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_BDF "long_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

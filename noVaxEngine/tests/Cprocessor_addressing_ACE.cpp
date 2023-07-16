//
// Created by chubr on 16.07.23.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include "test.h"


TEST(Cprocessor, byte_addressing_ACE) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_ACE "byte.v11");
    noVaxProcessor.step();
    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_ACE "byte_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}


TEST(Cprocessor, byte_addressing_ACE_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_ACE "byte_3op.v11");
    noVaxProcessor.step();
    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_ACE "byte_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}


TEST(Cprocessor, word_addressing_ACE) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_ACE "word.v11");
    noVaxProcessor.step();
    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_ACE "word_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, word_addressing_ACE_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_ACE "word_3op.v11");
    noVaxProcessor.step();
    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_ACE "word_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, long_addressing_ACE) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_ACE "long.v11");
    noVaxProcessor.step();
    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_ACE "long_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

TEST(Cprocessor, long_addressing_ACE_3op) {
    Cprocessor noVaxProcessor;
    noVaxProcessor.load(PATH_Cprocessor_addressing_ACE "long_3op.v11");
    noVaxProcessor.step();
    noVaxProcessor.step();
    noVaxProcessor.step();

    Cprocessor referenceSample;
    referenceSample.load(PATH_Cprocessor_addressing_ACE "long_3op_.v11");

    EXPECT_EQ(noVaxProcessor,referenceSample);
}

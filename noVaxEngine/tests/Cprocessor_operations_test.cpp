//
// Created by misha on 09.07.2023.
//
#include "gtest/gtest.h"
#include "../Cprocessor.h"
#include <cstdlib>

typedef BYTE uint8_t;

template<typename T>
void test_add() {
    Cprocessor testSubject;
    ASSERT_EQ(testSubject.add(T(0xD),T(0xB)), T(0x18));
    ASSERT_EQ(testSubject.getCFlag(), false);
}

TEST(Commands_add, add) {
    test_add<BYTE>();
    test_add<WORD>();
    test_add<DWORD>();
}

template<typename T>
void test_add_overflow() {
    Cprocessor testSubject;
    ASSERT_EQ(testSubject.add(T(std::numeric_limits<T>::max()),T(std::numeric_limits<T>::max())), T(std::numeric_limits<T>::max() - 1));
    ASSERT_EQ(testSubject.getCFlag(), true);
}

TEST(Commands_add, overflow) {
    test_add_overflow<BYTE>();
    test_add_overflow<WORD>();
    test_add_overflow<DWORD>();
}

template<typename T>
void test_add_carry() {
    Cprocessor testSubject;
    ASSERT_EQ(testSubject.add(T(std::numeric_limits<T>::max()),T(std::numeric_limits<T>::max() - 2), true), T(std::numeric_limits<T>::max() - 2));
    ASSERT_EQ(testSubject.getCFlag(), true);
}

TEST(Commands_add, carry) {
    test_add_carry<BYTE>();
    test_add_carry<WORD>();
    test_add_carry<DWORD>();
}

template<typename T>
void test_add_zero() {
    Cprocessor testSubject;
    ASSERT_EQ(testSubject.add(T(0x0),T(0x0)), T(0x0));
    ASSERT_EQ(testSubject.getCFlag(), false);
}

TEST(Commands_add, zero) {
    test_add_zero<BYTE>();
    test_add_zero<WORD>();
    test_add_zero<DWORD>();
}

template<typename T>
void test_sub() {
    Cprocessor testSubject;
    ASSERT_EQ(testSubject.sub(T(0x2),T(0x1)), T(0x1));
    ASSERT_EQ(testSubject.getCFlag(), false);
}

TEST(Commands_sub, sub) {
    test_sub<BYTE>();
    test_sub<WORD>();
    test_sub<DWORD>();
}

template<typename T>
void test_sub_overflow() {
    Cprocessor testSubject;
    ASSERT_EQ(testSubject.sub(T(std::numeric_limits<T>::max() - 1),T(std::numeric_limits<T>::max())), T(std::numeric_limits<T>::max()));
    ASSERT_EQ(testSubject.getCFlag(), true);
}

TEST(Commands_sub, overflow) {
    test_sub_overflow<BYTE>();
    test_sub_overflow<WORD>();
    test_sub_overflow<DWORD>();
}

template<typename T>
void test_sub_zero() {
    Cprocessor testSubject;
    ASSERT_EQ(testSubject.sub(T(0x0),T(0x0)), T(0x0));
    ASSERT_EQ(testSubject.getCFlag(), false);
}

TEST(Commands_sub, zero) {
    test_sub_zero<BYTE>();
    test_sub_zero<WORD>();
    test_sub_zero<DWORD>();
}
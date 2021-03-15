#include "complex.hpp"

#include <gtest/gtest.h>

TEST(ComplexTest, SimpleFunctionality)
{
  common::Complex<int> num{2, 4};
  ASSERT_EQ(num.real(), 2);
  ASSERT_EQ(num.imag(), 4);
  
  num.real(-8);
  num.imag(-3);
  ASSERT_EQ(num.real(), -8);
  ASSERT_EQ(num.imag(), -3);
  
  common::Complex<int> num2(num);
  ASSERT_EQ(num2.real(), -8);
  ASSERT_EQ(num2.imag(), -3);
  ASSERT_TRUE(num == num2);
}

TEST(ComplexTest, Subtraction)
{
  common::Complex<int> num1{-2, 4};
  common::Complex<int> num2{4, -9};
  
  auto num3 = num1 - num2;
  ASSERT_EQ(num3.real(), -6);
  ASSERT_EQ(num3.imag(), 13);
}

TEST(ComplexTest, Addition)
{
  common::Complex<int> num1{-2, 4};
  common::Complex<int> num2{4, -9};
  
  auto num3 = num1 + num2;
  ASSERT_EQ(num3.real(), 2);
  ASSERT_EQ(num3.imag(), -5);
}

TEST(ComplexTest, Multiply)
{
  common::Complex<int> num1{-2, 4};
  common::Complex<int> num2{4, -9};
  
  auto num3 = num1 * num2;
  ASSERT_EQ(num3.real(), 28);
  ASSERT_EQ(num3.imag(), 34);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();        
}

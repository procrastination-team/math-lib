#include "matrix.hpp"

#include <gtest/gtest.h>

TEST(MatrixTest, OperatorBrackets)
{
  common::Matrix<int> mx{2, 2};
  mx[0][0] = 34;
  ASSERT_EQ(mx[0][0], 34);
}

TEST(MatrixTest, Iterator)
{
  common::Matrix<int> mx{2, 2};
  mx[0][0] = 0;
  mx[0][1] = 1;
  mx[1][0] = 2;
  mx[1][1] = 3;
  int i = 0;
  for(auto it = mx.begin(); it != mx.end(); ++it)
  {
    ASSERT_EQ(*it, i);
    ++i;
  }
}

TEST(MatrixTest, Comparison)
{
  common::Matrix<int> mx{2, 2};
  mx[0][0] = 0;
  mx[0][1] = 1;
  mx[1][0] = 2;
  mx[1][1] = 3;
  
  common::Matrix<int> mx2{2, 2};
  mx2[0][0] = 0;
  mx2[0][1] = 1;
  mx2[1][0] = 2;
  mx2[1][1] = 3;
  
  ASSERT_TRUE(mx == mx2);
  
  mx2[0][0] = 234234;
  ASSERT_FALSE(mx == mx2);
}

TEST(MatrixTest, Addition)
{
  common::Matrix<int> mx{2, 2};
  mx[0][0] = 0;
  mx[0][1] = 1;
  mx[1][0] = 2;
  mx[1][1] = 3;
  
  common::Matrix<int> mx2{2, 2};
  mx2[0][0] = 4;
  mx2[0][1] = 5;
  mx2[1][0] = 6;
  mx2[1][1] = 7;
  
  auto res = mx + mx2;
  
  ASSERT_EQ(res[0][0], 4);
  ASSERT_EQ(res[0][1], 6);
  ASSERT_EQ(res[1][0], 8);
  ASSERT_EQ(res[1][1], 10);
}

TEST(MatrixTest, Subtraction)
{
  common::Matrix<int> mx{2, 2};
  mx[0][0] = 0;
  mx[0][1] = 1;
  mx[1][0] = 2;
  mx[1][1] = 3;
  
  common::Matrix<int> mx2{2, 2};
  mx2[0][0] = 12;
  mx2[0][1] = -7;
  mx2[1][0] = 1;
  mx2[1][1] = 0;
  
  auto res = mx - mx2;
  
  ASSERT_EQ(res[0][0], -12);
  ASSERT_EQ(res[0][1], 8);
  ASSERT_EQ(res[1][0], 1);
  ASSERT_EQ(res[1][1], 3);
}

TEST(MatrixTest, MultiplyOnScalar)
{
  common::Matrix<int> mx{2, 2};
  mx[0][0] = 0;
  mx[0][1] = 1;
  mx[1][0] = -2;
  mx[1][1] = -3;
  
  auto res = mx * 4;
  
  ASSERT_EQ(res[0][0], 0);
  ASSERT_EQ(res[0][1], 4);
  ASSERT_EQ(res[1][0], -8);
  ASSERT_EQ(res[1][1], -12);
}

TEST(MatrixTest, MultiplyMatrices)
{
  common::Matrix<int> mx{3, 2};
  mx[0][0] = 0;
  mx[0][1] = 1;
  mx[1][0] = 2;
  mx[1][1] = 3;
  mx[2][0] = 4;
  mx[2][1] = 5;
  
  common::Matrix<int> mx2{2, 4};
  mx2[0][0] = 1;
  mx2[0][1] = 2;
  mx2[0][2] = 3;
  mx2[0][3] = 4;
  mx2[1][0] = 5;
  mx2[1][1] = 6;
  mx2[1][2] = 7;
  mx2[1][3] = 8;
  
  auto res = mx * mx2;
  
  ASSERT_EQ(res.rows(), 3);
  ASSERT_EQ(res.colls(), 4);
  
  ASSERT_EQ(res[0][0], 5);
  ASSERT_EQ(res[0][1], 6);
  ASSERT_EQ(res[0][2], 7);
  ASSERT_EQ(res[0][3], 8);
  
  ASSERT_EQ(res[1][0], 17);
  ASSERT_EQ(res[1][1], 22);
  ASSERT_EQ(res[1][2], 27);
  ASSERT_EQ(res[1][3], 32);
  
  ASSERT_EQ(res[2][0], 29);
  ASSERT_EQ(res[2][1], 38);
  ASSERT_EQ(res[2][2], 47);
  ASSERT_EQ(res[2][3], 56);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();        
}

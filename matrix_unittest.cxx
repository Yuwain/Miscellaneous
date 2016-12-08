#include "matrix.hxx"
#include "gtest/gtest.h"

namespace {
  class MatrixTest : public ::testing::Test {
    protected:
      Matrix<int> mat;
      Matrix<int> mat2;
  };

  TEST_F(MatrixTest, resizeWorks) {
    mat.resize(1, 7);
    EXPECT_EQ(1, mat.rows());
    EXPECT_EQ(7, mat.cols());

    mat.resize(0, 0);
    EXPECT_EQ(0, mat.rows());
    EXPECT_EQ(0, mat.cols());

    mat.resize(0, 3);
    EXPECT_EQ(0, mat.rows());
    EXPECT_EQ(0, mat.cols());

    EXPECT_ANY_THROW(mat.resize(-1, -2));
    EXPECT_ANY_THROW(mat.resize(1, -2));
    EXPECT_ANY_THROW(mat.resize(-1, 2));
  }

  TEST_F(MatrixTest, setAllWorks) {
    mat.resize(3, 4);
    mat.set_all(2);
    for (size_t i = 0; i < mat.rows(); ++i) {
      for (size_t j = 0; j < mat.cols(); ++j) {
        ASSERT_EQ(2, mat[i][j]);
      }
    }
  }

  TEST_F(MatrixTest, operatorsWork) {
    mat.resize(1,4);
    mat2 = mat;

    mat.set_all(1);
    mat2.set_all(2);

    Matrix<int> temp = mat + mat2;

    ASSERT_NO_THROW(mat += mat2);
    EXPECT_EQ(temp, mat);

    mat2.set_all(0);

    ASSERT_NO_THROW(mat -= temp);
    EXPECT_EQ(mat, mat2);

    EXPECT_NO_THROW(mat[0][0] = 1);
    EXPECT_NO_THROW(mat[0][0]);
  }

  TEST_F(MatrixTest, constructorsWork) {
    EXPECT_NO_THROW(Matrix<int> m3(2, 2));
    mat.resize(3,4);
    mat2.resize(3,4);
    mat.set_all(3);
    mat2.set_all(5);
    Matrix<int> temp;

    EXPECT_NO_THROW(temp = mat2);
    EXPECT_EQ(temp, mat2);
    EXPECT_NO_THROW(temp = std::move(mat));
    EXPECT_NO_THROW(Matrix<int> m4(mat2));
    EXPECT_NO_THROW(Matrix<int> m4(std::move(mat2)));
  }
}

TEST(nonMemberOPs, equality) {
  Matrix<int> m1(3, 5), m2(3, 5);
  m1.set_all(3);
  m2.set_all(3);
  EXPECT_TRUE(m1 == m2);
  EXPECT_FALSE(m1 != m2);

  m2.set_all(4);
  EXPECT_FALSE(m1 == m2);
  EXPECT_TRUE(m1 != m2);
  
  Matrix<int> m3(4, 6);
  m3.set_all(4);
  EXPECT_FALSE(m2 == m3);
  EXPECT_TRUE(m2 != m3);
}

TEST(nonMemberOPs, addsub) {
  Matrix<int> m1(3, 5), m2(3, 5), m3(3, 5);
  m1.set_all(3);
  m2.set_all(5);
  m3.set_all(8);

  EXPECT_EQ(m1 + m2, m3);
  EXPECT_EQ(m3 - m2, m1);
}

TEST(nonMemberOPs, negative) {
  Matrix<int> m1(3, 5), m2(3, 5);
  m1.set_all(3);
  m2.set_all(-3);

  EXPECT_EQ(m1, -m2);
  EXPECT_EQ(-m1, m2);

  m2.set_all(0);
  EXPECT_EQ(m2, -m2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

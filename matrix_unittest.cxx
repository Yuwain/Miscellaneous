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
        ASSERT_EQ(2, mat.at(i, j));
      }
    }
  }

  TEST_F(MatrixTest, operatorsWork) {
    mat.resize(1,4);
    mat2 = mat;

    mat.set_all(1);
    mat2.set_all(2);

    Matrix<int> temp = mat + mat2;
    
    Matrix<int> fail(3,4);

    EXPECT_THROW(fail += temp, size_difference);
    EXPECT_THROW(fail -= temp, size_difference);
    EXPECT_NO_THROW(fail *= 2);
    EXPECT_NO_THROW(fail *= 2.0);
    EXPECT_NO_THROW(fail *= 'c');

    ASSERT_NO_THROW(mat += mat2);
    EXPECT_EQ(temp, mat);

    mat2.set_all(0);

    ASSERT_NO_THROW(mat -= temp);
    EXPECT_EQ(mat, mat2);

    mat.set_all(2);
    mat2.set_all(4);
    mat *= 2;
    EXPECT_EQ(mat, mat2);
  }

  TEST_F(MatrixTest, atWorks) {
    mat.resize(1,1);
    EXPECT_NO_THROW(mat.at(0, 0) = 1);
    EXPECT_NO_THROW(mat.at(0, 0));
    EXPECT_ANY_THROW(mat.at(10, 0));
    EXPECT_ANY_THROW(mat.at(0, 100));
  }

  TEST_F(MatrixTest, constructorsWork) {
    EXPECT_NO_THROW(Matrix<int> m3(2, 2));
    mat.resize(3,4);
    mat2.resize(3,4);
    mat.set_all(3);
    mat2.set_all(5);
    Matrix<int> temp;
    std::vector<std::vector<int>> vec = {{1, 2},{3,4},{5,6}};

    EXPECT_NO_THROW(temp = mat2);
    EXPECT_EQ(temp, mat2);
    EXPECT_NO_THROW(temp = std::move(mat));
    EXPECT_NO_THROW(Matrix<int> m4(mat2));
    EXPECT_NO_THROW(Matrix<int> m4(std::move(mat2)));
    EXPECT_NO_THROW(Matrix<int> m4(temp));
    Matrix<int> m4(vec);
    EXPECT_EQ(3, m4.rows());
    EXPECT_EQ(2, m4.cols());
    vec = {{1,2}, {3,4}, {5,6,7}};

    EXPECT_THROW(Matrix<int> m5(vec), jagged_matrix);
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

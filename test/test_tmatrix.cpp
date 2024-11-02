#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> A(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> A(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> A(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> A(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> B(A));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> A(7, 10);
    TDynamicMatrix<int> B(A);
    EXPECT_EQ(A, B);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> A(7, 7);
    TDynamicMatrix<int> B(A);
    EXPECT_EQ(A[0][0], B[0][0]);
    B[0][0] = 1;
    EXPECT_NE(B[0][0], A[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> A(7);
    ASSERT_NO_THROW(A.size());
    EXPECT_EQ(7, A.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> A(7);
    A[2][2] = 7;
    EXPECT_EQ(A[2][2], 7);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> A(7);
    EXPECT_ANY_THROW(A.at(-7, 2));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> A(7);
    EXPECT_ANY_THROW(A.at(7, 2));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> A(7);

    ASSERT_NO_THROW(A = A);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> A(7), B(7);
    ASSERT_NO_THROW(A = B);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> A(7), B(15);
    A = B;
    EXPECT_EQ(A.size(), 15);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> A(7), B(15);
    ASSERT_NO_THROW(A = B);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> A(7, 7), B(7, 7);
    B = A;
    EXPECT_TRUE(A == B);
}

TEST(TDynamicMatrix, compare_non_equal_matrices_return_false)
{
    TDynamicMatrix<int> A(7, 7), B(7, 8);
    EXPECT_FALSE(A == B);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> A(7);
    EXPECT_TRUE(A == A);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> A(7), B(15);
    EXPECT_FALSE(A == B);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> A(7), B(7);
    ASSERT_NO_THROW(A + B);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> A(7), B(10);
    ASSERT_ANY_THROW(A + B);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> A(7), B(7);
    ASSERT_NO_THROW(A - B);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> A(7), B(10);
    ASSERT_ANY_THROW(A - B);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    TDynamicMatrix<int> A(7), B(7);
    ASSERT_NO_THROW(A * B);
}

TEST(TDynamicMatrix, cant_multiply_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> A(7), B(10);
    ASSERT_ANY_THROW(A * B);
}

TEST(TDynamicMatrix, can_multiply_a_matrix_by_number)
{
    TDynamicMatrix<int> A(7, 5);
    A = A * 3;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            EXPECT_EQ(A[i][j], 15);
        }
    }
}

TEST(TDynamicMatrix, can_multiply_a_matrix_by_zero)
{
    TDynamicMatrix<int> A(7, 5), A0(7, 0);
    A = A * 0;
    EXPECT_TRUE(A == A0);
}

TEST(TDynamicMatrix, can_multiply_a_matrix_by_one)
{
    TDynamicMatrix<int> A(7, 5), copyA(7, 5);
    copyA = A * 1;
    EXPECT_TRUE(A == copyA);
}

TEST(TDynamicMatrix, can_multiply_a_matrix_by_vector)
{
    TDynamicMatrix<int> A(2);
    TDynamicVector<int> B(2), expected(2);
    B[0] = 1; B[1] = 4;
    expected[0] = 9; expected[1] = 24;
    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 4; A[1][1] = 5;
    EXPECT_TRUE(A * B == expected);
}

TEST(TDynamicMatrix, can_multiply_a_matrix_by_other_matrix)
{
    TDynamicMatrix<int> A(2), B(2), expected(2);
    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 4; A[1][1] = 5;
    B[0][0] = 1; B[0][1] = 3;
    B[1][0] = 4; B[1][1] = 9;
    expected[0][0] = 9; expected[0][1] = 21;
    expected[1][0] = 24; expected[1][1] = 57;
    EXPECT_TRUE(A * B == expected);
}

TEST(TDynamicMatrix, can_add_matrices)
{
    TDynamicMatrix<int> A(7), B(7), expected(7);
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            A[i][j] = i;
            B[i][j] = j;
            expected[i][j] = i + j;
        }
    }
    EXPECT_EQ(A + B, expected);
}

TEST(TDynamicMatrix, can_subtract_matrices)
{
    TDynamicMatrix<int> A(7), B(7), expected(7);
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            A[i][j] = i + j;
            B[i][j] = i;
            expected[i][j] = j;
        }
    }
    EXPECT_EQ(A - B, expected);
}

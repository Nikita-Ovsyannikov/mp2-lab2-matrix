#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(7));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-7));
}

TEST(TDynamicVector, can_create_vector_consisting_of_identical_numbers) 
{
	ASSERT_NO_THROW(TDynamicVector<int> v(7, 10));
}

TEST(TDynamicVector, correct_vals_in_vector_consisting_of_identical_numbers)
{
	TDynamicVector<int> v(7, 10);
	for (int i = 0; i < 7; i++) {
		ASSERT_EQ(v[i], 10);
	}
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int size = 10;
	TDynamicVector<int> a(size), b(size + 3);
	a[0] = 1;
	a[4] = 5;
	a[9] = 100;
	b = a;
	ASSERT_EQ(a, b);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int size = 10;
	TDynamicVector<int> a(size);
	TDynamicVector<int> b(a);
	ASSERT_NE(&a,&b);
}

TEST(TDynamicVector, can_create_vector_by_moving_constuctor)
{
    TDynamicVector<int> a(10);

    ASSERT_NO_THROW(TDynamicVector<int> b(std::move(a)));
}

TEST(TDynamicVector, correctly_work_memory_can_create_vector_by_moving_constuctor)
{
    TDynamicVector<int> a(10);
    TDynamicVector<int> b(std::move(a));

    EXPECT_EQ(&a[0], nullptr);
}

TEST(TDynamicVector, correct_values_when_create_vector_by_moving_constuctor)
{
    int mas[7] = { 1, 3, 5, 7, 9, 11, 13 };
    TDynamicVector<int> a(mas, 7);
    TDynamicVector<int> b(std::move(a));
    for (int i = 0; i < b.size(); i++) {
        EXPECT_EQ(b[i], 2 * i + 1);
    }
}

TEST(TDynamicVector, correct_size_when_create_vector_by_moving_constuctor)
{
    TDynamicVector<int> a(10);
    TDynamicVector<int> b(std::move(a));
    EXPECT_EQ(b.size(), 10);
    EXPECT_EQ(a.size(), 0);
}

TEST(TDynamicVector, can_create_vector_by_move_assignment_operator)
{
    TDynamicVector<int> a(10);
    TDynamicVector<int> b(56);

    ASSERT_NO_THROW(b = std::move(a));
}

TEST(TDynamicVector, correctly_work_memory_can_create_vector_by_move_assignment_operator)
{
    TDynamicVector<int> a(10);
    TDynamicVector<int> b(56);
    b = std::move(a);

    EXPECT_EQ(&a[0], nullptr);
}

TEST(TDynamicVector, correct_values_when_create_vector_by_move_assignment_operator)
{
    int mas[7] = { 1, 3, 5, 7, 9, 11, 13 };
    TDynamicVector<int> a(mas, 7);
    TDynamicVector<int> b(56);
    b = std::move(a);
    for (int i = 0; i < b.size(); i++) {
        EXPECT_EQ(b[i], 2 * i + 1);
    }
}

TEST(TDynamicVector, correct_size_when_create_vector_by_move_assignment_operator)
{
    TDynamicVector<int> a(10);
    TDynamicVector<int> b(56);
    b = std::move(a);
    EXPECT_EQ(b.size(), 10);
    EXPECT_EQ(a.size(), 0);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(7);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(7);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(7);
	ASSERT_ANY_THROW(v.at(7));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(7, 1);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(7, 2), v2(7, 10);
	ASSERT_NO_THROW(v2 = v1);
	for (int i = 0; i < 7; i++) {
		ASSERT_EQ(v2[i], 2);
	}
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(7, 2), v2(9, 10);
	v2 = v1;
	ASSERT_EQ(v1.size(), v2.size());	
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(7, 2), v2(9, 10);
	ASSERT_NO_THROW(v2 = v1);
	for (int i = 0; i < 7; i++) {
		ASSERT_EQ(v2[i], 2);
	}
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(7, 10), v2(7, 10);
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(7, 10);
	EXPECT_TRUE(v1 == v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(7, 10), v2(8, 10);
	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(7, 10);
	ASSERT_NO_THROW(v1 = v1 + 2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(7, 10);
	ASSERT_NO_THROW(v1 = v1 - 2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(7, 10);
	ASSERT_NO_THROW(v1 = v1 * 2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(7, 10), v2(7, 1), expectV(7, 11);
	ASSERT_EQ(expectV, v1 + v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(7, 10), v2(8, 1);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(7, 10), v2(7, 1), expectV(7, 9);
	ASSERT_EQ(expectV, v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(7, 10), v2(8, 1);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(7, 10), v2(7, 1);
	ASSERT_EQ(70, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(7, 10), v2(8, 1);
	ASSERT_ANY_THROW(v1 * v2);
}

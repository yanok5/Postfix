#include "stack.h"

#include <gtest.h>

TEST(Stack, can_create_stack)
{
	ASSERT_NO_THROW(Stack<int> s);
}

TEST(Stack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(Stack<int> s(MAX_STACK_SIZE + 1));
}

TEST(Stack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(Stack<int> s(10));
}

TEST(Stack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> s(-1));
}

TEST(Stack, cant_create_stack_with_very_big_length)
{
	ASSERT_ANY_THROW(Stack<int> s(1001));
}

TEST(Stack, can_push)
{
	Stack<int> s(2);
	ASSERT_NO_THROW(s.Push(1));
}

TEST(Stack, can_pop)
{
	Stack<int> s;
	ASSERT_ANY_THROW(s.Pop());
}

TEST(Stack, can_repack_when_push)
{
	Stack<int> s(1);
	s.Push(1);
	ASSERT_NO_THROW(s.Push(2));
	ASSERT_EQ(2, s.Top());
}

TEST(Stack, throws_when_free)
{
	Stack<int> s(2);
	ASSERT_ANY_THROW(s.Pop());
}

TEST(Stack, can_get_top)
{
	Stack<int> s(3);
	s.Push(1);
	ASSERT_NO_THROW(s.Top());
}

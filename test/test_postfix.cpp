#include "postfix.h"
#include <gtest.h>

TEST(Postfix, can_create_postfix)
{
	ASSERT_NO_THROW(Postfix p);
}

TEST(Stack, can_create_copied_postfix)
{
	Postfix p;
	ASSERT_NO_THROW(Postfix p1(p));
}

TEST(Postfix, can_get_infix)
{
	Postfix p("a+b");
	EXPECT_EQ("a+b", p.GetInfix());
}

TEST(Postfix, can_create_postfix_from_infix)
{
	Postfix p("a+b");
	p.ToPostfix();
	EXPECT_EQ("a b +", p.GetPostfix());
}

TEST(Postfix, CheckInfix_return_true_when_infix_is_correct)
{
	Postfix p("a+b");
	EXPECT_TRUE(p.CheckInfix());
}

TEST(Postfix, CheckInfix_return_false_when_infix_is_invalid)
{
	Postfix p("(a+-b");
	EXPECT_FALSE(p.CheckInfix());
}

TEST(Stack, throw_when_division_by_zero)
{
	Postfix p("2/0");
	ASSERT_ANY_THROW(p.Calculate());
}

TEST(Postfix, can_calculate_expression1)
{
	Postfix p("2+2*(2+2)");
	EXPECT_EQ(10, p.Calculate());
}

TEST(Postfix, can_calculate_expression2)
{
	Postfix p("(1+2)-3/6*2");
	EXPECT_EQ(2, p.Calculate());
}

TEST(Postfix, can_calculate_expression3)
{
	Postfix p("(0.5+0.5)/(0.25+0.25)");
	EXPECT_EQ(2, p.Calculate());
}

TEST(Postfix, can_calculate_expression4)
{
	Postfix p("0.1*(10*0.1)*(10/10)*100");
	EXPECT_EQ(10, p.Calculate());
}

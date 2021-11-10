#include<gtest/gtest.h>
#include"..\Lab_3_Stack\TStack.h"

TEST(TStack, can_create_Tstack)
{
  ASSERT_NO_THROW(TStack<int>s1);
  ASSERT_NO_THROW(TStack<char>s2);
  ASSERT_NO_THROW(TStack<double>s3);
  ASSERT_NO_THROW(TStack<int>s4(10));
}

TEST(TStack, cant_create_Tstack_with_negative_size)
{
  ASSERT_ANY_THROW(TStack<int>s(-5));
}

TEST(TStack, can_create_a_Tstack_of_Tstack)
{
  ASSERT_NO_THROW(TStack<TStack<int>>s);
}

TEST(TStack, can_add_element_to_stack)
{
  int a = 5;
  TStack<int>s;
  ASSERT_NO_THROW(s.push(a));
}

TEST(TStack, can_delete_element_to_stack)
{
  int a = 5;
  TStack<int>s;
  s.push(a);
  ASSERT_NO_THROW(s.pop());
}

TEST(TStack, cant_delete_element_if_stack_is_empty)
{
  TStack<int>s;
  ASSERT_ANY_THROW(s.pop());
}

TEST(TStack, check_empty_if_stack_is_empty_true)
{
  TStack<int>s;
  EXPECT_EQ(true, s.isEmpty());
  s.push(4);
  s.pop();
  EXPECT_EQ(true, s.isEmpty());
}

TEST(TStack, check_empty_if_stack_isnot_empty_false)
{
  TStack<int>s;
  s.push(0);
  EXPECT_EQ(false, s.isEmpty());
}

TEST(TStack, check_full_if_stack_isnot_full_false)
{
  TStack<int>s;//default size is 25
  EXPECT_EQ(false, s.isFull());
}

TEST(TStack, check_full_if_stack_is_full_true)
{
  TStack<int>s(2);
  s.push(0);
  s.push(0);
  EXPECT_EQ(true, s.isFull());
}

TEST(TStack, cant_add_too_many_elements)
{
  TStack<int>s(2);
  for (int i = 0; i < 2; i++)
  {
    s.push(i);
  }
  ASSERT_ANY_THROW(s.push(0));
}

TEST(TStack, can_get_size)
{
  TStack<int>s;
  ASSERT_NO_THROW(s.size());
  EXPECT_EQ(0, s.size());
}

TEST(TStack, get_size_is_right)
{
  TStack<int>s(100);
  for (size_t i = 0; i < 10; i++)
  {
    s.push(i);
  }
  EXPECT_EQ(10, s.size());
}

TEST(TStack, can_view_element_at_the_top)
{
  int a = 10;
  int b = 3;
  TStack<int>s;
  s.push(a);
  s.push(b);
  ASSERT_NO_THROW(s.top());
}

TEST(TStack, can_view_element_at_the_top_after_delete_el)
{
  TStack<int>s;
  s.push(1);
  s.push(4);
  s.push(2);
  s.pop();
  EXPECT_EQ(4, s.top());
}

TEST(TStack, cant_view_element_at_the_top_if_stack_is_empty)
{
  TStack<int>s;
  ASSERT_ANY_THROW(s.top());
}
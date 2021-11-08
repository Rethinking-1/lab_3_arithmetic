#include<gtest/gtest.h>
#include <Formula.h>

TEST(Formula, can_create_a_valid_formula)
{
  ASSERT_NO_THROW(Formula f("1+2"));
}

TEST(Formula, can_create_an_incorect_formula)
{
  ASSERT_NO_THROW(Formula f("wfewf"));
}

TEST(Formula, formula_checker_true_if_formula_is_correct)
{
  Formula f("(1+2^5)* (5+ (35-7))/133");
  EXPECT_EQ(true, f.FormulaChecker());
}

TEST(Formula, error_if_there_are_not_enough_arguments)
{
  Formula f("13**5");
  ASSERT_ANY_THROW(f.FormulaChecker());
}
TEST(Formula, error_if_extra_brackets)
{
  Formula f("4+((7*8)");
  ASSERT_ANY_THROW(f.FormulaChecker());
}

TEST(Formula, error_if_the_brackets_are_not_correct1)
{
  Formula f(")1+2");
  ASSERT_ANY_THROW(f.FormulaChecker());
}

TEST(Formula, error_if_the_brackets_are_not_correct2)
{
  Formula f("1+2(");
  ASSERT_ANY_THROW(f.FormulaChecker());
}

TEST(Formula, error_if_the_brackets_are_not_correct3)
{
  Formula f(")1+2(");
  ASSERT_ANY_THROW(f.FormulaChecker());
}


TEST(Formula, error_if_starts_with_multiplication)
{
  Formula f("*3+5");
  ASSERT_ANY_THROW(f.FormulaChecker());
}

TEST(Formula, error_if_starts_with_division)
{
  Formula f("/3+5");
  ASSERT_ANY_THROW(f.FormulaChecker());
}

TEST(Formula, error_if_there_are_forbidden_elements1)
{
  Formula f("325*17@9");
  ASSERT_ANY_THROW(f.FormulaChecker());
}

TEST(Formula, error_if_there_are_forbidden_elements2)
{
  Formula f("3+4`7! 4636 % 4465 -625*17#9_");
  ASSERT_ANY_THROW(f.FormulaChecker());
}
TEST(Formula, work_if_correct_and_start_with_minus)
{
  Formula f("-4+7");
  ASSERT_NO_THROW(f.FormulaChecker());
}

TEST(Formula, work_if_correct_and_start_with_plus)
{
  Formula f("+4+7");
  ASSERT_NO_THROW(f.FormulaChecker());
}

TEST(Formula, can_get_polish1)
{
  Formula f("1+2");
  EXPECT_EQ("1 2 + ", f.Get_PolishForm());
}

TEST(Formula, can_get_polish2)
{
  Formula f("1+2*(3-2)-4");
  EXPECT_EQ("1 2 3 2 - * + 4 - ", f.Get_PolishForm());
}

TEST(Formula, can_get_polish3)
{
  Formula f("1+2*(3-2)-4");
  EXPECT_EQ("1 2 3 2 - * + 4 - ", f.Get_PolishForm());
}

TEST(Formula, can_get_polish4)
{
  Formula f("1 + 2 / (3 - 3)");
  EXPECT_EQ("1 2 3 3 - / + ", f.Get_PolishForm());
}

TEST(Formula, can_get_polish5)
{
  Formula f("(5.5 + 6.2 * 7.0) * (13 - 2)");
  EXPECT_EQ("5.5 6.2 7.0 * + 13 2 - * ", f.Get_PolishForm());
}

TEST(Formula, can_get_polish6)
{
  Formula f("(5 * 6 ^ 7) * (13 - 2)");
  EXPECT_EQ("5 6 7 ^ * 13 2 - * ", f.Get_PolishForm());
}

TEST(Formula, can_get_polish7)
{
  Formula f("(((1 + 23) * 1 - 22) + 5) * 2 - 7");
  EXPECT_EQ("1 23 + 1 * 22 - 5 + 2 * 7 - ", f.Get_PolishForm());
}

TEST(Formula, cant_calculate_not_correct_formuls1)
{
  Formula f("*3+5");
  ASSERT_ANY_THROW(f.Calculate_Polish());
}
  
TEST(Formula, cant_calculate_not_correct_formuls2)
{
  Formula f("(((1+23)*1-22)+5)*2-(7");
  ASSERT_ANY_THROW(f.Calculate_Polish());
}

TEST(Formula, cant_calculate_not_correct_formuls3)
{
  Formula f("1++1");
  ASSERT_ANY_THROW(f.Calculate_Polish());
}

TEST(Formula, cant_calculate_if_division_by_zero)
{
  Formula f("1+7/(36 - 2* 18)");
  ASSERT_ANY_THROW(f.Calculate_Polish());
}

TEST(Formula, can_calculate_correct_formuls1)
{
  Formula f("1+2");
  ASSERT_NO_THROW(f.Calculate_Polish());
  EXPECT_EQ(3, f.Get_Ans());
}

TEST(Formula, can_calculate_correct_formuls2)
{
  Formula f("1+2*(3-2)-4");
  ASSERT_NO_THROW(f.Calculate_Polish());
  EXPECT_EQ(-1, f.Get_Ans());
}

TEST(Formula, can_calculate_correct_formuls3)
{
  Formula f("1+2*(3-2)-4");
  ASSERT_NO_THROW(f.Calculate_Polish());
  EXPECT_EQ(-1, f.Get_Ans());
}

TEST(Formula, can_calculate_correct_formuls4)
{
  Formula f("(((1+23)*1-22)+5)*2-7");
  ASSERT_NO_THROW(f.Calculate_Polish());
  EXPECT_EQ(7, f.Get_Ans());
}

TEST(Formula, can_calculate_correct_formuls5)
{
  Formula f("5-5");
  ASSERT_NO_THROW(f.Calculate_Polish());
  EXPECT_EQ(0, f.Get_Ans());
}

TEST(Formula, can_calculate_correct_formuls6)
{
  Formula f("(5 + 6 * 7)* (13 - 2)");
  ASSERT_NO_THROW(f.Calculate_Polish());
  EXPECT_EQ(517, f.Get_Ans());
}

TEST(Formula, can_calculate_correct_formuls7)
{
  Formula f("(5.5 + 6.2 * 7.0) * (13 - 2)");
  ASSERT_NO_THROW(f.Calculate_Polish());
  EXPECT_EQ(537.9, f.Get_Ans());
}

TEST(Formula, can_calculate_correct_formuls8)
{
  Formula f("(5,5 + 6,2 * 7,0) * (13 - 2)");
  ASSERT_NO_THROW(f.Calculate_Polish());
  EXPECT_EQ(537.9, f.Get_Ans());
}

TEST(Formula, can_print_lexem)
{
  Formula f("(5,5 + 6,2 * 7,0) * (13 - 2)");
  ASSERT_NO_THROW(f.PrintLexem());
}


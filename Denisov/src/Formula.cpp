//#include "Formula.h"
//Formula::Formula(std::string formula) :Formula_(formula), sizeFormula(formula.size()),Ans(0) {}
//
//bool Formula::FormulaChecker()
//{
//  if (CountErrorsbrackets())
//  {
//    std::cout << "Errors " << CountErrorsbrackets() << "\n" << "translation and reading is not possible\n";
//    throw std::exception();
//  }
//  if (!CheckCorrectOperation())
//  {
//    std::cout << "Not enough operands\n";
//    throw std::exception();
//  }
//  if (FindProhibitedOperations()!= "0")
//  {
//    std::cout << "Error: you have a prohibited operation is " << FindProhibitedOperations() << "\ntranslation and reading is not possible\n";
//    throw std::exception();
//  }
//  return true;
//}
//
//int Formula::CheckPriority(std::string str)
//{
//  if (str == "(" || str == ")")
//    return 0;
//  if (str == "+" || str == "-")
//    return 1;
//  if (str == "*" || str == "/")
//    return 2;
//  if (str == "^" || str == "%")
//    return 3;
//  if(str == "1","2","3","4","5","6","7","8","9","0",".")
//    return 4;
//  return -1;
//}
//void Formula::PrintLexem()
//{
//  Split_into_Lexems();
//  std::cout << "value lex: ";
//  for (int i = 0; i < LexDefForm.size(); i++)
//  {
//    std::cout << LexDefForm[i].getVal() << "|";
//  }
//  std::cout << "\n"  << "type lex:  ";
//  for (int i = 0; i < LexDefForm.size(); i++)
//  {
//    std::cout <<LexDefForm[i].gettype() << "|";
//  }
//  std::cout << "\n";
//}
//
//int Formula::CountErrorsbrackets()
//{
//  int temp = 0, errors = 0;
//  for (int i = 0; i < sizeFormula; i++)
//  {
//    if (Formula_[i] == '(')
//      temp++;
//    if (Formula_[i] == ')')
//    {
//      if (!temp)
//        errors++;
//      else
//        temp--;
//    }
//  }
//  return errors + temp;
//}
//
//bool Formula::CheckCorrectOperation()
//{
//  Split_into_Lexems();
//  if (CheckPriority(LexDefForm[0].getVal()) != 4 || CheckPriority(LexDefForm[0].getVal()) != 1|| LexDefForm[0].getVal() != "(")
//    return false;
//  for (size_t i = 1; i < LexDefForm.size(); i++)
//  {
//    if (CheckPriority(LexDefForm[i].getVal()) != 1 && CheckPriority(LexDefForm[i - 1].getVal()) != 1)
//      return false;
//    if(i == LexDefForm.size()-1 &&(CheckPriority(LexDefForm[i].getVal()) != 1 || LexDefForm[i].getVal() != ")"))
//      return false;
//  }
//  return true;
//}
//
//std::string Formula::FindProhibitedOperations()
//{
//  Split_into_Lexems();
//  for (size_t i = 0; i < LexDefForm.size(); i++)
//    if (LexDefForm[i].getVal() == "@", "_", "#", "!", "$", "&", "`", "~")
//      return LexDefForm[i].getVal();
//}
//
//bool Formula::Split_into_Lexems()
//{
//  if (LexDefForm.size())
//    return true;
//  if (!FormulaChecker())
//    return false;
//  for (int i = 0; i < sizeFormula; i++)
//  {
//    if (Formula_[i] != ' ')
//    {
//      std::string temp;
//      temp.push_back(Formula_[i]);
//      if (CheckPriority(temp) == 4)
//      {
//        std::string lex_val;
//        while (i < sizeFormula && Formula_[i] != ' ' && CheckPriority(temp) == 4)
//        {
//          lex_val += temp;
//          i++;
//          temp = "";
//          temp.push_back(Formula_[i]);
//        }
//        Lexema mlex(lex_val, 4);
//        LexDefForm.push_back(mlex);
//      }
//      else if(CheckPriority(temp)!=-1)
//      {
//        Lexema mlex(temp, CheckPriority(temp));
//        LexDefForm.push_back(mlex);
//      }
//    }
//  }
//  return true;
//}
//
////wrong!
//std::string Formula::FormulaConverter()
//{
//  if (!PostfixForm.empty())
//    return PostfixForm;
//  if (!FormulaChecker())
//    throw std::exception();
//  if (Formula_.size() < 2)
//  {
//    PostfixForm = Formula_;
//    return PostfixForm;
//  }
//  st.push(std::to_string(Formula_[0]));
//  for (int i = 1; i < sizeFormula; i++)
//  {
//    
//    if (Formula_[i] == '(' || CheckPriority(std::to_string(Formula_[i])) > CheckPriority(std::to_string(Formula_[i - 1])))
//    {
//      st.push(std::to_string(Formula_[i]));
//    }
//    else if (Formula_[i] == ')')
//    {
//      while (!st.isEmpty() && st.top() != "(")
//      {
//        PostfixForm.insert(PostfixForm.size(), st.top());
//        //PostfixForm.push_back(st.top());
//        st.pop();
//      }
//    }
//    else
//      while (!st.isEmpty() && CheckPriority(std::to_string(Formula_[i])) > CheckPriority(st.top()))
//      {
//        PostfixForm.insert(PostfixForm.size(), st.top());
//        st.pop();
//      }
//  }
//  return PostfixForm;
//}
//

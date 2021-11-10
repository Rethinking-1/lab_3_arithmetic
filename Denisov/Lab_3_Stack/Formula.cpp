#include "..\Lab_3_Stack\Formula.h"

Formula::Formula(std::string formula) :Formula_(formula), sizeFormula(formula.size()), Ans(0) {}

bool Formula::FormulaChecker()
{
  if (FindProhibitedOperations() != "0")
  {
    std::cout << "Error: you have a prohibited operation is " << FindProhibitedOperations() << "\ntranslation and reading is not possible\n";
    throw std::exception();
    return false;
  }

  if (CountErrorsbrackets())
  {
    std::cout << "Errors " << CountErrorsbrackets() << "\n" << "translation and reading is not possible\n";
    throw std::exception();
    return false;
  }
  if (!CheckCorrectOperation())
  {
    std::cout << "Error:Not enough operands\n";
    throw std::exception();
    return false;
  }
  return true;
}

int Formula::CheckPriority(std::string str)
{
  if (str == "(" || str == ")")
    return 0;
  if (str == "+" || str == "-")
    return 1;
  if (str == "*" || str == "/")
    return 2;
  if (str == "^" || str == "%")
    return 3;
  if (str == "1" || str == "2" || str == "3" || str == "4" || str == "5"
    || str == "6" || str == "7" || str == "8" || str == "9" || str == "0" || str == "." || str == ",")
    return 4;
  return -1;
}
void Formula::PrintLexem()
{
  Split_into_Lexems();
  std::cout << "value lex: ";
  for (int i = 0; i < LexDefForm.size(); i++)
  {
    std::cout << std::setfill(' ') << std::setw(4) << LexDefForm[i].getVal() << "|";
  }
  std::cout << "\n" << "type lex:  ";
  for (int i = 0; i < LexDefForm.size(); i++)
  {
    std::cout << std::setfill(' ') << std::setw(4) << LexDefForm[i].gettype() << "|";
  }
  std::cout << "\n";
}

int Formula::CountErrorsbrackets()
{
  int temp = 0, errors = 0;
  for (int i = 0; i < sizeFormula; i++)
  {
    if (Formula_[i] == '(')
      temp++;
    if (Formula_[i] == ')')
    {
      if (!temp)
        errors++;
      else
        temp--;
    }
  }
  return errors + temp;
}

bool Formula::CheckCorrectOperation()
{
  Split_into_Lexems();
  if (LexDefForm[0].gettype() != 4 && LexDefForm[0].gettype() != 1 && LexDefForm[0].getVal() != "(")
    return false;
  for (size_t i = 1; i < LexDefForm.size(); i++)
  {
    int a = LexDefForm[i].gettype();
    int b = LexDefForm[i - 1].gettype();
    if ((a == 1 || a == 2 || a == 3) && (b == 1 || b == 2 || b == 3))//
      return false;
    if (i == LexDefForm.size() - 1 && (LexDefForm[i].gettype() != 4 && LexDefForm[i].getVal() != ")"))
      return false;
  }
  return true;
}

std::string Formula::FindProhibitedOperations()
{
  std::string errors;
  for (size_t i = 0; i < Formula_.size(); i++)
  {
    if (Formula_[i] == ',')
      Formula_[i] = '.';
    char tmp = Formula_[i];
    if (tmp == '@' || tmp == '_' || tmp == '#' || tmp == '!' || tmp == '$' || tmp == '&' || tmp == '`' || tmp == '~')
      errors.push_back(tmp);
  }
  if (errors.empty())
    return "0";
  return errors;
}

bool Formula::Split_into_Lexems()
{
  if (LexDefForm.size())
    return true;
  for (int i = 0; i < sizeFormula; i++)
  {
    if (Formula_[i] != ' ')
    {
      std::string temp;
      temp.push_back(Formula_[i]);
      if (CheckPriority(temp) == 4)
      {
        std::string lex_val;
        while (i < sizeFormula && Formula_[i] != ' ' && CheckPriority(temp) == 4)
        {
          lex_val += temp;
          i++;
          temp = "";
          temp.push_back(Formula_[i]);
        }
        i--;
        Lexema mlex(lex_val, 4);
        LexDefForm.push_back(mlex);
      }
      else if (CheckPriority(temp) != -1)
      {
        Lexema mlex(temp, CheckPriority(temp));
        LexDefForm.push_back(mlex);
      }
    }
  }
  return true;
}


std::string Formula::FormulaConverter()
{
  int c_op_breaket = 0;
  Split_into_Lexems();
  if (!FormulaChecker())
    return "Error\n";
  PolishForm = "";
  if (LexDefForm[0].getVal() == "(")
    c_op_breaket++;
  if (LexDefForm[0].gettype() == 1)
  {
    PolishForm += "0 ";
  }
  if (LexDefForm[0].gettype() != 4)
  {
    st.push(LexDefForm[0].getVal());
  }
  else
    PolishForm = PolishForm + LexDefForm[0].getVal() + " ";
  for (int i = 1; i < LexDefForm.size(); i++)
  {
    if (LexDefForm[i].gettype() == 4)
      PolishForm = PolishForm + LexDefForm[i].getVal() + " ";

    else if (LexDefForm[i].getVal() == "(")
    {
      st.push(LexDefForm[i].getVal());
      c_op_breaket++;
    }
    else if (LexDefForm[i].getVal() == ")")
    {
      while (st.top() != "(")
      {
        PolishForm += st.top();
        PolishForm += " ";
        st.pop();
      }
      st.pop();
      c_op_breaket--;
    }

    else if (LexDefForm[i].gettype() != 0 || LexDefForm[i].gettype() != 4 || LexDefForm[i].gettype() != -1)//is an operation
    {
      if (st.size() - c_op_breaket == 0)
        st.push(LexDefForm[i].getVal());
      else
      {
        //if (LexDefForm[i].gettype() > CheckPriority(st.top()))
        //{
        // // PostfixForm += LexDefForm[i].getVal();
        //  st.push(LexDefForm[i].getVal());
        //}

        while (!st.isEmpty() && (LexDefForm[i].gettype() <= CheckPriority(st.top())))
        {
          if (st.top() != "(")
            PolishForm = PolishForm + st.top() + " ";

          st.pop();
        }
        st.push(LexDefForm[i].getVal());
      }
    }

    //  std::cout << PolishForm << "\n";
  }
  while (!st.isEmpty())
  {
    PolishForm += st.top();
    PolishForm += " ";
    st.pop();
    //  std::cout << PolishForm << "\n";
  }
  return PolishForm;
}

bool Formula::Calculate_Polish()
{
  FormulaChecker();
  FormulaConverter();
  Split_into_Lexems();
  for (int i = 0; i < /*LexDefForm.size()*/PolishForm.size(); i++)
  {
    std::string temp = "";
    double a = 0.0;
    double b = 0.0;
    while (PolishForm[i] != ' ')
    {
      temp.push_back(PolishForm[i]);
      i++;
    }
    if (CheckPriority(temp) != 1 && CheckPriority(temp) != 2 && CheckPriority(temp) != 3)
      st.push(temp);
    else
    {
      {//while(!st.isEmpty())

        a = std::stod(st.top());
        st.pop();
        b = std::stod(st.top());
        st.pop();
      }
      if (temp == "+")
        b += a;
      if (temp == "-")
        b -= a;
      if (temp == "*")
        b *= a;
      if (temp == "/")
      {
        if (a == 0)
        {
          std::cout << "Error: division by zero\n";
          throw std::exception();
          return false;
        }
        b /= a;
      }
      if (temp == "%")
      {
        if (fabs(a) < 1e-10)
        {
          std::cout << "Error: division by zero\n";
          throw std::exception();
          return false;
        }
        b = (int)b % (int)a;
      } 
      if (temp == "^")
        b = std::pow(b, a);
      st.push(std::to_string(b));
    }
  }
  //  if (LexDefForm[i].gettype() == 4)
  //  {
  //    st.push(LexDefForm[i].getVal());
  //  }
  //  if (LexDefForm[i].gettype() == 1 || LexDefForm[i].gettype() == 2 || LexDefForm[i].gettype() == 3) 
  //  {
  //    double a = std::stod(st.top());
  //    st.pop();
  //    double b = std::stod(st.top());
  //    st.pop();
  //    if (LexDefForm[i].getVal() == "+")
  //      b += a;
  //    if (LexDefForm[i].getVal() == "-")
  //      b -= a;
  //    if (LexDefForm[i].getVal() == "*")
  //      b *= a;
  //    if (LexDefForm[i].getVal() == "/")
  //      if (a == 0)
  //      {
  //        std::cout << "Error: division by zero\n";
  //        throw std::exception();
  //        return false;
  //      }
  //    if (LexDefForm[i].getVal() == "%")
  //      if (a == 0)
  //      {
  //        std::cout << "Error: division by zero\n";
  //        throw std::exception();
  //        return false;
  //      }
  //    if (LexDefForm[i].getVal() == "^")
  //      b = std::pow(b, a);
  //    st.push(std::to_string(b));
  //  }
  //}
  Ans = std::stod(st.top());
  return true;
}

double Formula::Get_Ans()
{
  return Ans;
}
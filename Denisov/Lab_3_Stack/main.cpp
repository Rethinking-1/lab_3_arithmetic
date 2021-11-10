#include"Formula.h"
#include<stack>
using namespace std;
int main()
{
  string s;
  cout << "Enter the expression\n";
  getline(cin, s);
  Formula f(s);
  if (f.FormulaChecker())
  {
    cout << "Errors 0\n";
    f.FormulaConverter();
    cout << "Stlit into Lexems\n";
    f.PrintLexem();
    cout << "Polish form:\n" << f.Get_PolishForm() << "\n";
    f.Calculate_Polish();
    cout << "Result:" << f.Get_Ans();
  }
  return 0;
}
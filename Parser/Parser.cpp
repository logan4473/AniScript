#include<string>
#include<memory>
#include<map>
#include<iostream>
#include<utility>
#include"Lexer/Lexer.h"

class ExprAST {
public:
  virtual ~ExprAST() = default;
};

class NumberExprAST : public ExprAST {
  std::string Val;

public:
  NumberExprAST(std::string Val) : Val(Val) {}
};

class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {}
};

class BinaryExprAST : public ExprAST {
  char Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
                std::unique_ptr<ExprAST> RHS)
    : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

std::pair<int,std::string> getNextToken() {
  std::pair<int,std::string> curTokenPair = getToken();
  int curToken = curTokenPair.first;
  std::string curTokenString = curTokenPair.second;
  std::cout<<curToken<<" "<<curTokenString<<std::endl;
  return curTokenPair;
}

std::map<char, int> BinopPrecedence;

std::unique_ptr<ExprAST> ParseNumberExpr(std::string curTokenString) {
  auto Result = std::make_unique<NumberExprAST>(curTokenString);
  getNextToken();
  return std::move(Result);
}

int main() {
  BinopPrecedence['<'] = 10;
  BinopPrecedence['>'] = 10;
  BinopPrecedence['+'] = 20;
  BinopPrecedence['-'] = 20;
  BinopPrecedence['*'] = 40;
  BinopPrecedence['^'] = 50;
  while(getNextToken().first!=tok_exit);
  return 0;
}
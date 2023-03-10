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
  std::string Value;
public:
  VariableExprAST(const std::string &Name,const std::string &Value){ this->Name = Name; this->Value = Value; }
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
  std::cout<<"Parsed Number "<<curTokenString<<std::endl;
  return std::move(Result);
}

std::unique_ptr<ExprAST> ParseIdentifierExpr(std::string curTokenString) {
  std::string IdName = curTokenString;

  std::pair<int,std::string> curTokenPair = getToken();
  int curToken = curTokenPair.first;
  curTokenString = curTokenPair.second;

  if(curTokenString != "="); //Error Handler

  curTokenPair = getToken();
  curToken = curTokenPair.first;
  curTokenString = curTokenPair.second;

  std::string IdValue = curTokenString;

  return std::make_unique<VariableExprAST>(IdName,IdValue);
}

static std::unique_ptr<ExprAST> ParsePrimary(std::pair<int,std::string> curTokenPair) {
  
  int curToken = curTokenPair.first;
  std::string curTokenString = curTokenPair.second;

  switch (curToken) {
  default:
    //Error Handler
    break;
  case tok_identifier:
    return ParseIdentifierExpr(curTokenString);
  case tok_number:
    return ParseNumberExpr(curTokenString);
  }
}

static std::unique_ptr<ExprAST> ParseExpression(std::pair<int,std::string> curTokenPair) {
  auto LHS = ParsePrimary(curTokenPair);
  if (!LHS)
    return nullptr;

  // return ParseBinOpRHS(0, std::move(LHS));
}

int main() {
  BinopPrecedence['<'] = 10;
  BinopPrecedence['>'] = 10;
  BinopPrecedence['+'] = 20;
  BinopPrecedence['-'] = 20;
  BinopPrecedence['*'] = 40;
  BinopPrecedence['^'] = 50;

  std::pair<int,std::string> curTokenPair = getToken();
  int curToken = curTokenPair.first;
  std::string curTokenString = curTokenPair.second;

  while(curToken!=tok_exit) {
    
    if(curToken==tok_number) ParseNumberExpr(curTokenString);

    if(curToken==tok_identifier) ParseIdentifierExpr(curTokenString);

    curTokenPair = getToken();
    curToken = curTokenPair.first;
    curTokenString = curTokenPair.second;
  };
  return 0;
}
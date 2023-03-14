#include<string>
#include<memory>
#include<map>
#include<iostream>
#include<utility>
#include"Lexer/Lexer.h"

class ExprAST {
public:
  virtual ~ExprAST() = default;
  virtual Value *codegen() = 0;
};

class NumberExprAST : public ExprAST {
  std::string Val;
   Value *codegen() override;

public:
  NumberExprAST(std::string Val) : Val(Val) {}
};

class VariableExprAST : public ExprAST {
  std::string Name;
  std::string Val;
public:
  VariableExprAST(const std::string &Name,const std::string &Value){ this->Name = Name; this->Val = Val; }
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

  std::cout<<"Variable :"<<IdName<<", Value :"<<IdValue<<std::endl;

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

static std::unique_ptr<ExprAST> ParseBinOpRHS(int curToken,int ExprPrec, std::unique_ptr<ExprAST> LHS) {
  while (true) {
    int TokPrec = BinopPrecedence[curToken];

    if (TokPrec < ExprPrec)
      return LHS;

    int BinOp = curToken;
    std::pair<int,std::string> curTokenPair = getToken();
    curToken = curTokenPair.second[0];
    std::string curTokenString = curTokenPair.second;

    auto RHS = ParsePrimary(curTokenPair);
    if (!RHS)
      return nullptr;
    
    int NextPrec = BinopPrecedence[curToken];
    if (TokPrec < NextPrec) {
      RHS = ParseBinOpRHS(curToken,TokPrec + 1, std::move(RHS));
      if (!RHS)
        return nullptr;
    }

    LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
  }
}

static std::unique_ptr<ExprAST> ParseExpression(std::pair<int,std::string> curTokenPair) {
  auto LHS = ParsePrimary(curTokenPair);
  if (!LHS)
    return nullptr;

  return ParseBinOpRHS(curTokenPair.second[0],0, std::move(LHS));
}

static std::unique_ptr<ExprAST> ParseParenExpr() {
  std::pair<int,std::string> curTokenPair = getToken();
  auto V = ParseExpression(curTokenPair);
  if (!V)
    return nullptr;
  curTokenPair = getToken();
  int curToken = curTokenPair.first;
  std::string curTokenString = curTokenPair.second;
  if (curTokenString != ")"); //Error handler
  return V;
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

    if(curTokenString=="(") ParseParenExpr();

    curTokenPair = getToken();
    curToken = curTokenPair.first;
    curTokenString = curTokenPair.second;
  };
  return 0;
}
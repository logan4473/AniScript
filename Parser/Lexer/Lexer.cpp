#include<string>
#include<iostream>
#include"DFA/IdentifyToken.h"


static int getToken() {
  static int lastChar = ' ';
  std::string tokenString;

  while(isspace(lastChar)) lastChar = getchar();

  while(!isspace(lastChar) && lastChar != '\n') {
    tokenString += lastChar;
    lastChar = getchar();
  }

  int keywordCheck = keyword(tokenString);

  if(keywordCheck!=0) {
    std::cout<<"Keyword : "<<tokenString<<std::endl;
    return keywordCheck;
  }

  if(identifier(tokenString)) {
    std::cout<<"Id : "<<tokenString<<std::endl;
    return tok_identifier;
  }

  if(numbers(tokenString)) { 
    std::cout<<"Number : "<<tokenString<<std::endl;
    return tok_number;
  }

  if(literal(tokenString)) {
    std::cout<<"Literal : "<<tokenString<<std::endl;
    return tok_literal;
  }


  if (lastChar == EOF)
  return tok_eof;

  int ThisChar = lastChar;
  lastChar = getchar();
  return ThisChar;

}

int main() {
  while(getToken()!=tok_exit);
  return 0;
}
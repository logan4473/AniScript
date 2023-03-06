#include"DFA/IdentifyToken.h"

std::pair<int,std::string> getToken() {
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
    return {keywordCheck,tokenString};
  }

  if(identifier(tokenString)) {
    std::cout<<"Id : "<<tokenString<<std::endl;
    return {tok_identifier,tokenString};
  }

  if(numbers(tokenString)) { 
    std::cout<<"Number : "<<tokenString<<std::endl;
    return {tok_number,tokenString};
  }

  if(literal(tokenString)) {
    std::cout<<"Literal : "<<tokenString<<std::endl;
    return {tok_literal,tokenString};
  }


  if (lastChar == EOF)
  return {tok_eof,tokenString};

  int ThisChar = lastChar;
  lastChar = getchar();
  return {ThisChar,tokenString};

}
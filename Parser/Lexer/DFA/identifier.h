#ifndef IDENTIFIER_H
#define IDENTIFIER_H

bool identifier(int& lastChar,std::string& tokenString) {
  if(!isalnum(lastChar)) return false;

  tokenString += lastChar;
  
  while(isalnum(lastChar = getchar())) tokenString += lastChar;

  int keywordCheck = keyword(tokenString);

  if(keywordCheck != 0) return false;

  std::cout<<"Token identified : "<<tokenString<<std::endl;

  return true;

}

#endif
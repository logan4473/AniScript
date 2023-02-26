#ifndef IDENTIFIER_H
#define IDENTIFIER_H

bool identifier(int& lastChar,std::string& tokenString) {
  if(!isalnum(lastChar)) return false;

  tokenString += lastChar;
  
  while(isalnum(lastChar = getchar())) tokenString += lastChar;

  std::cout<<"Token identified : "<<tokenString<<std::endl;

  if(tokenString=="exit") return false;

  return true;

}

#endif
#ifndef IDENTIFIER_H
#define IDENTIFIER_H

bool identifier(std::string& tokenString) {

  auto it = tokenString.begin();

  if(isdigit(*it)) return false;

  ++it;
  
  while(isalnum(*it)) it++;

  int keywordCheck = keyword(tokenString);

  if(keywordCheck != 0) return false;

  std::cout<<"Token identified : "<<tokenString<<std::endl;

  return true;

}

#endif
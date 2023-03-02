#ifndef IDENTIFIER_H
#define IDENTIFIER_H

bool identifier(std::string& tokenString) {

  std::string::iterator it = tokenString.begin();

  if(!isalpha(*it)) return false;

  ++it;
  
  while(isalnum(*it)) it++;

  return (it==tokenString.end());

}

#endif
#include<string>
#include<iostream>
#include"DFA/IdentifyToken.h"


static int getToken() {
  static int lastChar = ' ';
  std::string tokenString;

  while(isspace(lastChar)) lastChar = getchar();

  if(identifier(lastChar,tokenString)) return tok_identifier;

  if(tokenString == "exit") return tok_exit;

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
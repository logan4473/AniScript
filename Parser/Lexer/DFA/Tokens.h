#ifndef TOKENS_H
#define TOKENS_H

enum Tokens {

  //commands
  tok_eof = 1,

  //data
  tok_identifier,
  tok_number,
  tok_literal,

  //keywords
  tok_exit,
  tok_if,
  tok_else
};

#endif
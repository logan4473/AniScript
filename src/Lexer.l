%{
    #include <string>
    #include <iostream>
    #include "AstNode.h"
    #include "Parser.h"

    #define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
    #define TOKEN(t) (yylval.token = t)

    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-register"
%}

IDENTIFIER     [a-zA-Z][a-zA-Z0-9_]*
NUMBER [0-9]+|[0-9]+[.][0-9]+|[0-9]+[.][0-9]+e[0-9]+
STRING ["].*["]

%%
[\t] ;
{IDENTIFIER} {SAVE_TOKEN; return TOK_IDENTIFIER;}
{NUMBER} {SAVE_TOKEN; return TOK_NUMBER;}
\n		{return TOK_NEWLINE;}
"+"		{return TOK_PLUS;}
"-"		{return TOK_MINUS;}
"*"		{return TOK_MUL;}
"/"		{return TOK_DIV;}
"="		{return TOK_ASSIGN;}
"=="	{return TOK_EQUAL;}
"!="    {return TOK_NEQUAL;}
"or"	{return TOK_OR;}
"and"	{return TOK_AND;}
"xor"	{return TOK_XOR;}
"<<"	{return TOK_LSHIFT;}
">>"	{return TOK_RSHIFT;}
.       {std::cerr<<"Syntax Error OwO \n"; yyterminate();}
%%


int yywrap() {
  // see man flex for now
  return 1;
}

#pragma clang diagnostic pop
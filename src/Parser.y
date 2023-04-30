%{
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "AstNode.h"

extern int yylex();
void yyerror(const char*);
Ani::Block *program;
%}

%union {
  Ani::Node *node;
  Ani::Block *block;
  Ani::Expression *expr;
  Ani::Statement *stmt;
  Ani::Identifier *ident;
  Ani::VariableDeclaration *var_decl;
  std::vector<Ani::VariableDeclaration*> *var_vec;
  std::vector<Ani::Expression*> *expr_vec;
  std::string *string;
  int token;
}

%token <string> TOK_IDENTIFIER TOK_NUMBER
%token <token> TOK_ASSIGN TOK_EQUAL TOK_NEQUAL
%token <token> TOK_LPAREN TOK_RPAREN TOK_LBRACE TOK_RBRACE TOK_COMMA
%token <token> TOK_PLUS TOK_MINUS TOK_MUL TOK_DIV


%type <ident> ident
%type <expr> numeric expr
%type <var_vec> func_decl_args
%type <expr_vec> call_args
%type <block> program stmts block
%type <stmt> stmt var_decl func_decl
%type <token> comparison


%left TOK_PLUS TOK_MINUS
%left TOK_MUL TOK_DIV

%start program

%%

program : stmts { program = $1; };
        ;

stmts : stmt { $$ = new Ani::Block(); $$->statements.push_back($<stmt>1); }
      | stmts stmt { $1->statements.push_back($<stmt>2); }
      ;

stmt : var_decl | func_decl
      | expr { $$ = new Ani::ExpressionStatement(*$1); }
      ;

block : TOK_LBRACE stmts TOK_RBRACE { $$ = $2; }
      | TOK_LBRACE TOK_RBRACE { $$ = new Ani::Block(); }
      ;

var_decl : ident ident { $$ = new Ani::VariableDeclaration(*$1, *$2); }
         | ident ident TOK_ASSIGN expr { $$ = new Ani::VariableDeclaration (*$1, *$2, $4); }
         ;

func_decl : ident ident TOK_LPAREN func_decl_args TOK_RPAREN block
            { $$ = new Ani::FunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; }
          ;

func_decl_args : { $$ = new Ani::Variables(); }
               | var_decl { $$ = new Ani::Variables(); $$->push_back($<var_decl>1); }
               | func_decl_args TOK_COMMA var_decl { $1->push_back($<var_decl>3); }
               ;

ident : TOK_IDENTIFIER { $$ = new Ani::Identifier(*$1); delete $1; }
      ;

numeric : TOK_NUMBER { $$ = new Ani::Number(stod($1->c_str())); delete $1; }
        ;

expr : ident TOK_ASSIGN expr { $$ = new Ani::Assignment(*$<ident>1, *$3); }
     | ident TOK_LPAREN call_args TOK_RPAREN { $$ = new Ani::MethodCall(*$1, *$3); delete $3; }
     | ident { $<ident>$ = $1; }
     | numeric
     | expr comparison expr {$$ = new Ani::BinaryOperator(*$1, $2, *$3); }
     | TOK_LPAREN expr TOK_RPAREN { $$ = $2; }
     ;

call_args : { $$ = new Ani::Expressions(); }
          | expr { $$ = new Ani::Expressions(); $$->push_back($1); }
          | call_args TOK_COMMA expr { $1->push_back($3); }
          ;

comparison : TOK_EQUAL | TOK_NEQUAL | TOK_PLUS | TOK_MINUS | TOK_MUL | TOK_DIV
           ;

%%

void yyerror(const char *str) {
  std::cerr << "Error: " << str << std::endl;
  std::exit(1);
}
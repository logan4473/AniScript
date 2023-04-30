#include <iostream>
#include "codegen.h"
#include "AstNode.h"

extern int yyparse();
extern Ani::Block *program;

int main(int argc, char *argv[]) {

    yyparse();
    std::cout << "Address of program in memory: " << program << std::endl;
    Ani::LLVMCodeGenContext context;
    context.generateCode(*program);
    context.runCode();

    return 0;
}
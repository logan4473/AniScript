%{
    int count = 0;
%}

%%
[0-9]+|[0-9]+"."[0-9]+ {count++;}
. ;
\n ;
"exit" {return 0;}
%%

int yywrap(){}

int main() {
    yylex();
    printf("%d\n",count);
    return 0;
}
// Program to recognize a valid arithmetic expression that uses operator +, –, * and /.

%{
    #include <stdio.h>
    #include <stdlib.h>

    extern int yylex();
    void yyerror(char *msg);
%}

%token id 
%token num

%left '/' '*' '+' '-'

// The context free grammar corresponding to a valid expression is given by
// E -> E/E, E*E, E+E, E-E, (E)
// All operators are left associative.

%%

S   :   E '\n'      { 
                        printf("Valid expression\n"); 
                        exit(0);
                    }
    ;

E   :   E '/' E
    |   E '*' E
    |   E '+' E
    |   E '-' E
    |   '(' E ')'
    |   id
    |   num
    ;

%%

// Function prints the message "Invalid expression" if the token does not match the context free grammar.
void yyerror(char *error) {
    printf("Invalid expression\n");
    exit(0);
}

void main() {
    printf("Enter an expression: ");
    yyparse();
}
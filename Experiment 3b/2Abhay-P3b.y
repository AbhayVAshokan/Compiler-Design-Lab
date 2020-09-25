// Implementation of Calculator using LEX and YACC.

%{
    #include <stdio.h>
    #include <stdlib.h>

    extern int yylex();
    void yyerror(char *msg);
%}

%token num

%left '(' ')'
%left '/'
%left '+'
%left '*'
%left '-'

// The context free grammar corresponding for the calculator is as follows.
// E -> E - E | F
// F -> F + F | G
// G -> G * G | H
// H -> H / H | I
// I -> (I)   | J
// J -> num
// All operators are left associative.

%%

S   :   E '\n'      {
                        printf("The result of the expression is %d\n",$$);
                        exit(0);
                    }
    ;

E   :   E '-' E     { $$ = $1 - $3; }
    |   F
    ;

F   :   F '+' F     { $$ = $1 + $3; }
    |   G
    ;

G   :   G '*' G     { $$ = $1 * $3; }
    |   H
    ;

H   :   H '/' H     { $$ = $1 / $3; }
    |   I
    ;

I   :   '(' I ')'   { $$ = $1; }
    |   J
    ;

J   : num
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
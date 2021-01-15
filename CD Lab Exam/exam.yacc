 // Implement a syntax analyzer in yacc for structure declaration statements in c.

%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(char *error);

    extern int yylex();
    extern int lineCounter;
%}

%token STRUCT TYPE ID

// The context free grammar for a structure declaration is given by:
// STRUCTURE -> STRUCT ID BLOCK;
// BLOCK -> { CODE }
// CODE -> STATEMENT CODE | STATEMENT
// STATEMENT -> TYPE IDLIST;
// IDLIST -> ID, IDLIST | ID

%%

STRUCTURE               :       STRUCT ID BLOCK ';'
                        |       STRUCT ID BLOCK IDLIST ';'
                        ;

BLOCK                   :       '{' CODE '}'
                        ;

CODE                    :       STATEMENT CODE 
                        |       STATEMENT
                        ;

STATEMENT               :       TYPE IDLIST ';'
                        ;

IDLIST                  :       ID ',' IDLIST
                        |       ID
                        ;

%%

// The program prints the message "Invalid Structure Declaration. Error at line number <num>" if the token does not match the context free grammar. Else, it displays "VALID STRUCTURE DECLARATION".
extern FILE *yyin;

int main(int argc, char *argv[]) {
    char filename[100];

    // Input the file name of the program
    printf("Enter the file name of the program: ");
    scanf("%s", filename);

    // Open file
    FILE *fptr = fopen(filename, "r");

    if(fptr == NULL) {
        printf("File does not exist or you don't have the permission to open it.\n");
        return 1;
    }

    yyin = fptr;
    yyparse();

    printf("\nValid Structure Declaration\n");
    return 0; 
}

void yyerror(char *error) {
    printf("\n%s\n", error);
    printf("\nInvalid Structure Declaration. Error at line number %d\n", lineCounter);
    exit(0);
}

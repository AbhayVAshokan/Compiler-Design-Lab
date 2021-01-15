 // Implement a syntax analyzer in yacc for structure declaration statements in c.

%{
    #include "y.tab.h"

    // Line counter is used to keep track of the line number at which error occurred.
    int lineCounter = 1;
%}

%%

 // Step 1: Tokenize the following keywords
 //         1. struct as STRUCT
 //         2. int, char, float as TYPE
 // Step 2: Tokenize identifiers as ID using regular expressions.

int                             |
char                            |
float                           |
double                          |
long                            |
char\*                          |
int\*                           |
float\*                         |
long\*                          return TYPE;

struct                          return STRUCT;

[_a-zA-Z][_a-zA-Z0-9]*          return ID;

[ \t]                           ;

\n                              lineCounter++;

.                               return yytext[0];

%%

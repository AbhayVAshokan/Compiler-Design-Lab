 // Convert the BNF rules into YACC form and write code to generate abstract syntax tree.

%{
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"

    int lineCounter = 1;
%}

%%

 // 1. Identifying some keywords
 // 2. Identifying identifiers and numbers
 // 3. Identifying logical operators

main\(\)                        return MAIN;
if                              return IF;
else                            return ELSE;
while                           return WHILE;

int         |
char        |
float                           return TYPE;

[a-zA-Z][_a-zA-Z0-9]*           {
                                    strcpy(yylval.var, yytext);
                                    return VAR;
                                }
[0-9]+|([0-9]*\.[0-9]+)         {
                                    strcpy(yylval.var, yytext);
                                    return NUM;
                                }

\<          |
\>          |
\>=         |
\<=         |
==                              {
                                    strcpy(yylval.var, yytext);
                                    return RELOP;
                                }

[ \t]                           ;
\n                              lineCounter++;
.                               return yytext[0];

%%

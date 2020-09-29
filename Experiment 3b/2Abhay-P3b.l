 // Implementation of calculator using LEX and YACC.

%{
    #include <stdlib.h>
    #include "y.tab.h"

    extern int yylval;
%}

%%

 // Recognize numbers and operators

[0-9]+?             {
                        yylval = atoi(yytext);
                        return num;
                    }

[-/+*\n]            return yytext[0];
")"                 return yytext[0];
"("                 return yytext[0];    
.                   ;

%%

 int yywrap() {
     return 1;
 }
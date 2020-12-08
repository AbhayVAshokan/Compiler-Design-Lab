 // Implement intermediate code generation for simple expressions.

%{
    #include "y.tab.h"
%}

%%

[0-9]+    {return digit;}
[a-z]+    {return id;}
[ \t]     ;
[\n]      {return 0;}
. {return yytext[0];}

%%

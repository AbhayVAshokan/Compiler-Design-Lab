 // Implement intermediate code generation for simple expressions.

%{ 
   #include <stdio.h>
   #include <string.h>
   #include "y.tab.h"
   #include "lex.yy.c"
%}

%token id digit  
%left '+''-'      
%left '*''/'
%left '^'
%right'='
%nonassoc UMINUS

%%

S  :  id { push(); }'='E { pop(); }
E  :  E'+' { push(); }T { pop3(); }
   |  E'-' { push(); }T { pop3(); }
   |  T
   ;

T  :  T'*' { push(); }F { pop3(); }
   |  T'/' { push(); }F { pop3(); }
   |  T'^'{ push(); }F { pop3(); }
   |  F
   ;

F  :  id { push(); }
   |  digit { push(); }
   |  '('E')'
   |  '-' { push(); }F { pop2(); } %prec UMINUS
   ;

%%

char stack[10][10], var[10] = "\0", temp[10] = "\0";
int top = 0;
char i = '0';

int main() { 
   yyparse();
   yylex();
   return 0;
}

yyerror(char *s) { 
 printf("%s\n",s);
}

push() { 
   top++;
   strcpy(stack[top], yytext);
}

pop3() { 
   printf("\nt%c=%s%s%s",i,stack[top - 2], stack[top - 1], stack[top]);
   top=top - 2;
   temp[0] = i;
   strcpy(var, "t");
   strcat(var, temp);
   strcpy(stack[top], var);
   i++;
}

pop() { 
   printf("\n%s=%s\n",stack[top - 1], stack[top]);
}

pop2() { 
   printf("\nt%c=%s%s",i,stack[top-1],stack[top]);
   top--;
   temp[0] = i;
   strcpy(var, "t");
   strcat(var, temp);
   strcpy(stack[top], var);
   i++;  
}

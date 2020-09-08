 // Implement lexical analyzer using lex tool

%%

 // Step 1: Ignore comments and pre-processor directives and functions.
 // Step 2: Identify string and integer/floating literals
 // Step 3: Identify keywords
 // Step 4: Identify identifiers   
 // Step 5: Identify operators 
 // Step 6: Identify characters like ',' and ';'

#.*                             ;
\/\/.*                          ;
\/\*.*                          ;
.*\*\/.*                        ;
.*\(.*\).*                      ;

[1-9][0-9]*\.?[0-9]*            printf("%s ", yytext);
\".*\"                          printf("%s ", yytext);

auto        |
break       |
case        |
char        |
continue    |
do          |
default     |
const       |
double      |
else        |
enum        |
extern      |
for         |
if          |
goto        |
float       |
int         |
long        |
register    |
return      |
signed      |
static      |
sizeof      |
short       |
struct      |
switch      |
typedef     |
union       |
void        |
while       |
volatile    |
unsigned                        printf("kwd ");

[_a-zA-Z][_a-zA-Z0-9]*          printf("id ");

\+                              printf("oper-add ");
\-                              printf("oper-sub ");
\*                              printf("oper-mul ");
\/                              printf("oper-div ");
\%                              printf("oper-mod ");
\=                              printf("oper-equ ");

[,;]                            printf("\b%s ", yytext);

.                               ;

%%

int yywrap() {
    return(1);
}

int main() {
    FILE *fp;
    char filename[50];

    // Input the file name of the program
    printf("Enter the file name of the program: ");
    scanf("%s", filename);

    // Open file
    fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("File does not exist or you don't have the permission to open it.\n");
        return 1;
    }

    // Read contents from file
    yyin = fp;
    yylex();

    return 1;
}



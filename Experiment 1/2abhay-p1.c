// Design and implement a lexical analyzer for given language using C. The lexical analyzer should ignore redundant spaces, tabs and newlines.

#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdlib.h>

// Function protypes
void skipLine(FILE *file);
int checkKeyword(char token[]);
int checkIdentifier(char token[]);
int isNumber(char token[], int size);

void main()
{
    FILE *file;
    char filename[50];

    // Input the file name of the program
    printf("Enter the file name of the program: ");
    scanf("%s", filename);

    // Open file
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File does not exist or you don't have the permission to open it.");
        exit(0);
    }

    // Read contents from file
    int i = 0;
    char ch, token[50];
    while ((ch = fgetc(file)) != EOF)
    {
        // Step 1: Ignore comments
        if (ch == '/')
        {
            if (fgetc(file) == '/')
                skipLine(file);
            else
                fseek(file, -1, SEEK_CUR);

            i = 0;
        }

        // Step 2: Ignoring preprocessor directives
        else if (ch == '#')
            skipLine(file);

        else if(ch == '(') {
            i = 0;
            token[i] = '\0';
        }

        // Printing strings as it is
        else if(ch == '\"') {
            do {
                ch = getc(file);
                printf("%c", ch);
            } while(ch != '\"');
            printf(" ");
        }


        else if (!isalnum(ch))
        {
            token[i] = '\0';

            // Step 3: Check whether it is a keyword
            if (checkKeyword(token))
                printf("kwd ");

            // Step 4: Check whether it is an identifier
            else if (checkIdentifier(token))
                printf("id ");

            else if(isNumber(token, i)) 
                printf("%s ", token);

            i = 0;

            switch (ch)
            {
            case '+':
                printf("oper-add ");
                break;
            case '-':
                printf("oper-sub ");
                break;
            case '*':
                printf("oper-mul ");
                break;
            case '/':
                printf("oper-div ");
                break;
            case '=':
                printf("oper-equ ");
                break;
            case ',':
               
            case ';':
                printf("\b%c", ch);
                break;
            }
        }
        else
            token[i++] = ch;
    }

    printf("\n");
    fclose(file);
}

// Function: Returns 1 if the token is a reserved keyword. Else it returns 0.
int checkKeyword(char token[])
{
    // List of all valid keywords
    const char *keywords[] = {
        "auto",
        "break",
        "case",
        "char",
        "continue",
        "do",
        "default",
        "const",
        "double",
        "else",
        "enum",
        "extern",
        "for",
        "if",
        "goto",
        "float",
        "int",
        "long",
        "register",
        "return",
        "signed",
        "static",
        "sizeof",
        "short",
        "struct",
        "switch",
        "typedef",
        "union",
        "void",
        "while",
        "volatile",
        "unsigned",
    };

    for (int i = 0; i < 32; i++)
    {
        if (strcmp(*(keywords + i), token) == 0)
            return 1;
    }
    return 0;
}

// Function: Returns 1 if the token is a valid identifier. Else it returns 0.
int checkIdentifier(char token[])
{
    // Regular expression for a valid C identifier
    regex_t regex;
    char *pattern = "[_a-zA-Z][_a-zA-Z0-9]{0,30}";

    // Compare token against the regular expression
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0)
        return 0;
    int status = regexec(&regex, token, 0, NULL, 0);
    regfree(&regex);
    if (status != 0)
        return 0;

    return 1;
}

// Function to skip the current line
void skipLine(FILE *file)
{
    char ch;
    int condition = 1;
    char *comment;
    do
    {
        ch = fgetc(file);
        condition = !(ch == '\n' || ch == EOF);
    } while (condition);
}

// Function: Returns 1 if the token is a number. Else it returns 0.
int isNumber(char token[], int size) {
    for(int i=0; i<size; i++) {
        if(!isdigit(token[i]))
            return 0;
    }
    return 1;
}
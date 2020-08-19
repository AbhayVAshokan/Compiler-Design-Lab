// Design and implement a lexical analyzer for given language using C. The lexical analyzer should ignore redundant spaces, tabs and newlines.

#include <ctype.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

// Function protypes
void skipLine(FILE *file);
int checkKeyword(char token[]);
int checkIdentifier(char token[]);
int isNumber(char token[], int size);
void skipMultilineComment(FILE *file);

void main() {
    FILE *file;
    char filename[50];

    // Input the file name of the program
    printf("Enter the file name of the program: ");
    scanf("%s", filename);

    // Open file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("File does not exist or you don't have the permission to open it.");
        exit(0);
    }
    printf("\n----- ANALYSED OUTPUT -----\n");

    // Read contents from file
    int i = 0;
    char ch, token[50];
    while ((ch = fgetc(file)) != EOF) {
        switch (ch) {
        // Step 1: Ignore comments and pre-processor directives and functions.
        case '/':
            ch = getc(file);

            // Multiline comments
            if (ch == '*') {
                skipMultilineComment(file);
                break;
            }
        case '#':
            skipLine(file);
        case '(':
            token[i] = '\0';
            if (strcmp(token, "main") == 0)
                printf("\b\b\b\b");

            i = 0;
            token[i] = '\0';
            break;

        // Step 2: Print strings as it is.
        case '\"':
            printf("\"");
            do {
                ch = getc(file);
                printf("%c", ch);
            } while (ch != '\"');
            printf(" ");
            break;

        default:
            // Every token is separated by a non-alphanumeric character.
            if (!isalnum(ch)) {
                token[i] = '\0';

                // Step 3: Check if token is a keyword
                if (checkKeyword(token))
                    printf("kwd ");

                // Step 4: Check if token is an identifier
                else if (checkIdentifier(token))
                    printf("id ");

                // Step 5: Check if token is a number
                else if (isNumber(token, i))
                    printf("%s ", token);

                i = 0;

                switch (ch) {
                // Step 6: Check if character is an operator
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
                case '%':
                    printf("oper-mod ");
                    break;
                case '=':
                    printf("oper-equ ");
                    break;

                // Step 7: Check for other separators
                case ',':
                case ';':
                    printf("\b%c", ch);
                    break;
                }
            }
            else
                token[i++] = ch;
        }
    }

    printf("\n");
    fclose(file);
}

// Function: Returns 1 if the token is a reserved keyword. Else it returns 0.
int checkKeyword(char token[]) {
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
        if (strcmp(*(keywords + i), token) == 0)
            return 1;
    return 0;
}

// Function: Returns 1 if the token is a valid identifier. Else it returns 0.
int checkIdentifier(char token[]) {
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

// Function: Returns 1 if the token is a number. Else it returns 0.
int isNumber(char token[], int size) {
    if (size == 0)
        return 0;
    for (int i = 0; i < size; i++)
    {
        if (!isdigit(token[i]))
            return 0;
    }
    return 1;
}

// Function: Skip the current line
void skipLine(FILE *file) {
    char ch;
    int condition = 1;
    char *comment;
    do
    {
        ch = fgetc(file);
        condition = !(ch == '\n' || ch == EOF);
    } while (condition);
}

// Function: Skip multiline comment
void skipMultilineComment(FILE *file) {
    char ch = getc(file), nextChar;
    while (1) {
        if (ch == '*') {
            char nextChar = getc(file);
            if (nextChar == '/')
                return;
            else
                fseek(file, -1, SEEK_CUR);
        }
        ch = getc(file);
    }
}
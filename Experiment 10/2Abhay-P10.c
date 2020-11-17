// Construct a recursive descent parser for an expression

#include <stdio.h>
#include <ctype.h>
#include <string.h>

char expression[10];
int count, flag;
void check();
void Tprime();

void T() {
    check();
    Tprime();
}


void Eprime() {
    if (expression[count] == '+') {
        count++;
        T();
        Eprime();
    }
}

void E() {
    T();
    Eprime();
}

void check() {
    if (isalnum(expression[count]))
        count++;
    else if (expression[count] == '(') {
        count++;
        E();
        if (expression[count] == ')')
            count++;
        else
            flag = 1;
    }
    else
        flag = 1;
}

void Tprime() {
    if (expression[count] == '*') {
        count++;
        check();
        Tprime();
    }
}

int main() {
    count = 0;
    flag = 0;
    printf("\nEnter an expression: ");
    scanf("%s", expression);
    E();

    if ((strlen(expression) == count) && (flag == 0))
        printf("\nValid expression\n");
    else
        printf("\nInvalid expression\n");
}

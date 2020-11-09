// Write program to find ε – closure of all states of any given NFA with ε transition.

#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *link;
};

int findalpha(char);
void print_e_closure(int);
void findclosure(int, int);
void insert_trantbl(int, char, int);

char alphabet[20], c;
static int e_closure[20][20] = { 0 };
struct node *transition[20][20] = { NULL };
static int set[20], nostate, noalpha, s, notransition, r, buffer[20];

void main() {
    int i, j, k, m, t, n;
    struct node *temp;

    // 1. Accept the number of alphabets
    // 2. Accept the alphabet set
    // 3. Accept the number of states
    // 4. Accept the number of transactions
    // 5. Accept the transactions

    printf("Enter the number of alphabets: ");
    scanf("%d", &noalpha);
    getchar();

    printf("Enter the alphabet set: ");
    for (i = 0; i < noalpha; i++) {
        alphabet[i] = getchar();
        getchar();
    }

    printf("Enter the number of states: ");
    scanf("%d", &nostate);

    printf("Enter no of transition: ");
    scanf("%d", &notransition);

    printf("Enter transitions\n");
    for (i = 0; i < notransition; i++) {
        scanf("%d %c %d", &r, &c, &s);
        insert_trantbl(r, c, s);
    }

    printf("\ne-closure of states");
    for (i = 1; i <= nostate; i++) {
        c = 0;
        for (j = 0; j < 20; j++) {
            buffer[j] = 0;
            e_closure[i][j] = 0;
        }

        findclosure(i, i);
        printf("\ne-closure(q%d): ", i);
        print_e_closure(i);
    }

    printf("\n");
}

// Function to find the epsilon closure.
void findclosure(int x, int sta) {
    struct node *temp;
    int i;
    if (buffer[x])
        return;
    e_closure[sta][c++] = x;
    buffer[x] = 1;
    if (alphabet[noalpha - 1] == 'e' && transition[x][noalpha - 1] != NULL) {
        temp = transition[x][noalpha - 1];
        while (temp != NULL) {
            findclosure(temp->value, sta);
            temp = temp->link;
        }
    }
}

// Function to create NFA from the entered transaction.
void insert_trantbl(int r, char c, int s) {
    int j;
    struct node *temp;

    j = findalpha(c);
    if (j == -1) {
        printf("\nError: Alphabet not recognized.");
        exit(0);
    }

    temp = (struct node *)malloc(sizeof(struct node));
    temp->value = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}

// Function to find the index of alphabet in the set.
int findalpha(char c) {
    int i;
    for (i = 0; i < noalpha; i++)
        if (alphabet[i] == c)
            return i;
    return -1;
}

// Function to print the epsilon closure
void print_e_closure(int i) {
    int j;
    printf("{ ");
    for (j = 0; e_closure[i][j] != 0; j++)
        printf("q%d, ", e_closure[i][j]);
    printf("}");
}

// Sample Input
// 4
// a b c e
// 3
// 5
// 1 a 1
// 2 b 2
// 3 c 3
// 1 e 2
// 2 e 3
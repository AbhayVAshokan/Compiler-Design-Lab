// Write program to convert NFA with ε transition to NFA without ε transition.      

#include <stdio.h>
#include <stdlib.h>

struct node{
    int st;
    struct node *link;
};

static int set[20], nostate, noalpha, s, notransition, nofinal, start, finalstate[20], c, r, buffer[20], e_closure[20][20] = {0};
char alphabet[20];
struct node *transition[20][20] = {NULL};

void findclosure(int x, int sta) {
    struct node *temp;
    
    if (buffer[x])
        return;

    e_closure[sta][c++] = x;
    buffer[x] = 1;

    if (alphabet[noalpha - 1] == 'e' && transition[x][noalpha - 1] != NULL) {
        temp = transition[x][noalpha - 1];
        while (temp != NULL) {
            findclosure(temp->st, sta);
            temp = temp->link;
        }
    }
}

int findalpha(char c) {
    int i;
    for (i = 0; i < noalpha; i++)
        if (alphabet[i] == c)
            return i;

    return (999);
}

void insert_trantbl(int r, char c, int s) {
    int j;
    struct node *temp;
    j = findalpha(c);
    if (j == 999)
    {
        printf("error\n");
        exit(0);
    }
    temp = (struct node *)malloc(sizeof(struct node));
    temp->st = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}

void unionclosure(int i) {
    int j = 0, k;
    while (e_closure[i][j] != 0)
    {
        k = e_closure[i][j];
        set[k] = 1;
        j++;
    }
}

void findfinalstate() {
    int i, j, k, t;
    for (i = 0; i < nofinal; i++) {
        for (j = 1; j <= nostate; j++) {
            for (k = 0; e_closure[j][k] != 0; k++) {
                if (e_closure[j][k] == finalstate[i]) 
                    print_e_closure(j);
            }
        }
    }
}

void print_e_closure(int i) {
    printf("{");
    for (int j = 0; e_closure[i][j] != 0; j++)
        printf("q%d,", e_closure[i][j]);
    printf("}\t");
}

void main() {
    int i, j, k, m, t, n;
    struct node *temp;

    // 1. Accept the number of alphabets
    // 2. Accept the alphabet set
    // 3. Accept the number of states
    // 4. Accept the start state
    // 5. Accept the number of final states
    // 6. Accept the final states.
    // 7. Accept the number of transactions
    // 8. Accept the transactions

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

    printf("Enter the start state: ");
    scanf("%d", &start);

    printf("Enter the number of final states: ");
    scanf("%d", &nofinal);

    printf("Enter the final states: ");
    for (i = 0; i < nofinal; i++)
        scanf("%d", &finalstate[i]);

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

    printf("\n\nEquivalent NFA without epsilon\n");

    printf("Start state: ");
    print_e_closure(start);

    printf("\nAlphabets: ");
    for (i = 0; i < noalpha; i++)
        printf("%c, ", alphabet[i]);

    printf("\nStates: ");
    for (i = 1; i <= nostate; i++) {
         printf("{ ");
        for (int j = 0; e_closure[i][j] != 0; j++)
            printf("q%d, ", e_closure[i][j]);
        printf("} ");
    }
    
    printf("\n\nFinal states: ");
    findfinalstate();

    printf("\n\nNFA TRANSITION TABLE\n\n");
    for (i = 1; i <= nostate; i++) {
        for (j = 0; j < noalpha - 1; j++) {
            for (m = 1; m <= nostate; m++)
                set[m] = 0;

            for (k = 0; e_closure[i][k] != 0; k++) {
                t = e_closure[i][k];
                temp = transition[t][j];

                while (temp != NULL) {
                    unionclosure(temp->st);
                    temp = temp->link;
                }
            }

            printf("\n");

            print_e_closure(i);
            printf("%c\t", alphabet[j]);

            printf("{");
            for (n = 1; n <= nostate; n++) {
                if (set[n] != 0)
                    printf("q%d,", n);
            }
            printf("}");
        }
    }
    printf("\n");
}

// Sample Input
// 4
// a b c e
// 3
// 1
// 1
// 3
// 5
// 1 a 1
// 2 b 2
// 3 c 3
// 1 e 2
// 2 e 3
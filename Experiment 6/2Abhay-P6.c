// Write a program to convert epsilon NFA to DFA.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

char NFA_FILE[MAX_LEN];
char buffer[MAX_LEN];
int zz = 0, last_index = 0, symbols;
FILE *fp;

// structure to store DFA states and their status ( i.e new entry or already present)
struct DFA {
    char *states;
    int count;
} dfa;

// reset the hash map
void reset(int ar[], int size) {
    for (int i = 0; i < size; i++)
        ar[i] = 0;
}

// check which States are present in the e-closure map the states of NFA to a hash set
void check(int ar[], char S[]) {
    int j;

    // To parse the individual states of NFA
    int len = strlen(S);
    for (int i = 0; i < len; i++) {
        // Set hash map for the position of the states which is found
        j = ((int)(S[i]) - 65);
        ar[j]++;
    }
}
// To find new Closure States
void state(int ar[], int size, char S[]) {
    int k = 0;

    // Combine multiple states of NFA to create new states of DFA
    for (int j = 0; j < size; j++) {
        if (ar[j] != 0)
            S[k++] = (char)(65 + j);
    }
    
    // mark the end of the state
    S[k] = '\0';
}

// To pick the next closure from closure set
int closure(int ar[], int size) {
    int i;

    // check new closure is present or not
    for (i = 0; i < size; i++) {
        if (ar[i] == 1)
            return i;
    }

    return (100);
}

// check new DFA states can be entered in DFA table or not
int indexing(struct DFA *dfa) {
    for (int i = 0; i < last_index; i++) {
        if (dfa[i].count == 0)
            return 1;
    }
    return -1;
}

// to display epsilon closure
void displayEClosure(int states, int closure_ar[], char *closure_table[], char *NFA_TABLE[][symbols + 1], char *DFA_TABLE[][symbols]) {
    for (int i = 0; i < states; i++) {
        reset(closure_ar, states);
        closure_ar[i] = 2;

        // to neglect blank entry
        if (strcmp(&NFA_TABLE[i][symbols], "-") != 0) {
            // copy the NFA transition state to buffer
            strcpy(buffer, &NFA_TABLE[i][symbols]);
            check(closure_ar, buffer);
            int z = closure(closure_ar, states);

            // till closure get completely saturated
            while (z != 100) {
                if (strcmp(&NFA_TABLE[z][symbols], "-") != 0) {
                    strcpy(buffer, &NFA_TABLE[z][symbols]);
                    // call the check function
                    check(closure_ar, buffer);
                }

                closure_ar[z]++;
                z = closure(closure_ar, states);
            }
        }

        // print the e closure for every states of NFA
        printf("\ne-Closure (%c): ", (char)(65 + i));
        bzero((void *)buffer, MAX_LEN);
        state(closure_ar, states, buffer);
        strcpy(&closure_table[i], buffer);
        printf("%s ", &closure_table[i]);
    }
}

// to check new states in DFA
int new_states(struct DFA *dfa, char S[]) {
    // To check the current state is already being used as a DFA state or not in DFA transition table
    for (int i = 0; i < last_index; i++) {
        if (strcmp(&dfa[i].states, S) == 0)
            return 0;
    }

    // push the new set the count for new states entered to zero
    strcpy(&dfa[last_index++].states, S);
    dfa[last_index - 1].count = 0;
    return 1;
}

// Transition function from NFA to DFA (generally union of closure operation )
void trans(char S[], int M, char *clsr_t[], int st, char *NFT[][symbols + 1], char TB[]) {
    int len = strlen(S), i, j, k, g, arr[st], sz;
    char temp[MAX_LEN], temp2[MAX_LEN];
    char *buff;

    reset(arr, st);

    // Transition function from NFA to DFA
    for (i = 0; i < len; i++) {
        j = ((int)(S[i] - 65));
        strcpy(temp, &NFT[j][M]);

        if (strcmp(temp, "-") != 0) {
            sz = strlen(temp);
            g = 0;

            while (g < sz) {
                k = ((int)(temp[g] - 65));
                strcpy(temp2, &clsr_t[k]);
                check(arr, temp2);
                g++;
            }
        }
    }
    
    bzero((void *)temp, MAX_LEN);
    state(arr, st, temp);
    if (temp[0] != '\0')
        strcpy(TB, temp);
    else
        strcpy(TB, "-");
}

// display DFA transition state table
void displayDFA(int last_index, struct DFA *dfa_states, char *DFA_TABLE[][symbols]) {
    int i, j;

    printf("\n\nStates of DFA: ");
    for (i = 1; i < last_index; i++)
        printf("%s, ", &dfa_states[i].states);
    printf("\n");

    printf("Given symbols for DFA: \t");
    for (i = 0; i < symbols; i++)
        printf("%d, ", i);
    
    printf("\n\nDFA TRANSITION STATE TABLE");
    printf("\n\nStates: ");
    for (i = 0; i < symbols; i++)
        printf("|%d\t", i);
    printf("\n");

    // display the DFA transition state table
    printf("--------+-------+---\n");
    for (i = 0; i < zz; i++) {
        printf("%s\t", &dfa_states[i + 1].states);
        for (j = 0; j < symbols; j++)
            printf("|%s \t", &DFA_TABLE[i][j]);
        printf("\n");
    }
}

int main() {
    int i, j, states;
    char T_buf[MAX_LEN];
    
    // creating an array dfa structures
    struct DFA *dfa_states = malloc(MAX_LEN * (sizeof(dfa)));
    states = 6, symbols = 2;
    
    printf("States of NFA: ");
    for (i = 0; i < states; i++)
        printf("%c, ", (char)(65 + i));
    printf("\n");
    
    printf("Given symbols for NFA: \t");
    for (i = 0; i < symbols; i++)
        printf("%d, ", i);
    printf("eps");
    printf("\n\n");

    char *NFA_TABLE[states][symbols + 1];
    char *DFA_TABLE[MAX_LEN][symbols];
    strcpy(&NFA_TABLE[0][0], "FC");
    strcpy(&NFA_TABLE[0][1], "-");
    strcpy(&NFA_TABLE[0][2], "BF");
    strcpy(&NFA_TABLE[1][0], "-");
    strcpy(&NFA_TABLE[1][1], "C");
    strcpy(&NFA_TABLE[1][2], "-");
    strcpy(&NFA_TABLE[2][0], "-");
    strcpy(&NFA_TABLE[2][1], "-");
    strcpy(&NFA_TABLE[2][2], "D");
    strcpy(&NFA_TABLE[3][0], "E");
    strcpy(&NFA_TABLE[3][1], "A");
    strcpy(&NFA_TABLE[3][2], "-");
    strcpy(&NFA_TABLE[4][0], "A");
    strcpy(&NFA_TABLE[4][1], "-");
    strcpy(&NFA_TABLE[4][2], "BF");
    strcpy(&NFA_TABLE[5][0], "-");
    strcpy(&NFA_TABLE[5][1], "-");
    strcpy(&NFA_TABLE[5][2], "-");

    printf("NFA STATE TRANSITION TABLE");
    printf("\n\nStates: ");
    for (i = 0; i < symbols; i++)
        printf("|%d\t", i);
    printf("eps\n");
    printf("--------+-------+-------+---\n");
    for (i = 0; i < states; i++) {
        printf("%c\t", (char)(65 + i));
        for (j = 0; j <= symbols; j++)
            printf("|%s \t", &NFA_TABLE[i][j]);
        printf("\n");
    }

    int closure_ar[states];
    char *closure_table[states];
    
    displayEClosure(states, closure_ar, closure_table, NFA_TABLE, DFA_TABLE);
    
    strcpy(&dfa_states[last_index++].states, "-");
    dfa_states[last_index - 1].count = 1;
    bzero((void *)buffer, MAX_LEN);
    strcpy(buffer, &closure_table[0]);
    strcpy(&dfa_states[last_index++].states, buffer);

    int Sm = 1, ind = 1;
    int start_index = 1;
    // filling up the DFA table with transition values till new states can be entered in DFA table
    while (ind != -1) {
        dfa_states[start_index].count = 1;
        Sm = 0;
        
        for (i = 0; i < symbols; i++) {
            trans(buffer, i, closure_table, states, NFA_TABLE, T_buf);
            // storing the new DFA state in buffer
            strcpy(&DFA_TABLE[zz][i], T_buf);
            // parameter to control new states
            Sm = Sm + new_states(dfa_states, T_buf);
        }

        ind = indexing(dfa_states);
        if (ind != -1)
            strcpy(buffer, &dfa_states[++start_index].states);
        zz++;
    }

    displayDFA(last_index, dfa_states, DFA_TABLE);
    return 0;
}

// Write a program to perform loop unrolling.

#include <stdio.h>

int countbit1(unsigned int n) {
    int bits = 0, i = 0;

    while (n != 0) {
        if (n & 1) {
            printf("%d -> ", n);
            bits++;
        }
        n >>= 1;
        i++;
        printf("%d\n", n);
    }
    
    // i is the number of digits in the binary representation of n (number of iterations taken to compute bits).
    // bits is the number of 1s in the binary representation of n.
    printf("\nNumber of iterations: %d", i);
    return bits;
}

int countbit2(unsigned int n) {
    int bits = 0, i = 0;
    while (n != 0) {
        printf("%d -> ", n);
        if (n & 1)
            bits++;
        if (n & 2)
            bits++;
        if (n & 4)
            bits++;
        if (n & 8)
            bits++;
        n >>= 4;
        i++;
        printf("%d\n", n);
    }
    
    // i is the number of iterations taken to compute bits (number of digits of n / 4).
    // bits is the number of 1s in the binary representation of n.
    printf("\nNumber of iterations: %d", i);
    return bits;
}

void main() {
    unsigned int n;
    int x;
    char ch;

    printf("Enter the value for N: ");
    scanf("%u", &n);
    printf("\nMENU\n1. Loop Roll\n2. Loop UnRoll\n");
    printf("\nEnter your choice: ");
    scanf(" %c", &ch);

    switch (ch) {
    case '1':
        x = countbit1(n);
        printf("\nLoop Roll: Count of  1's: %d", x);
        break;
    case '2':
        x = countbit2(n);
        printf("\nLoop UnRoll:  Count of 1's: %d", x);
        break;
    default:
        printf("\n Wrong Choice\n");
    }

    printf("\n");
}

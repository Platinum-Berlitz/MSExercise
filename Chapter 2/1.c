/**
 * File name: 1.c
 * Description: Exercise 1, Chapter 2
 * Author: P. H. Berlitz
 * Version: 0.0.1
 * Date: 2018/03/14
 * Comments: may overflow rapidly for using int
 */

#include <stdio.h>
#define MAX_PART 100

int binom(const int a, const int b);
int factional(const int a);
int calcDegen(const int i, const int N, const int p);

int main(void) {
    int p, N, q = 0;
    int st[MAX_PART];

    printf("Enter the number of identical compartments (p):\n");
    scanf("%d", &p);
    printf("Enter the number of molecules (N < MAX_PART = 100):\n");
    scanf("%d", &N);

    printf("%d\t%d\n", factional(N), binom(p,N));
    for(int i = 0; i <= N; i++) {
        st[i] = calcDegen(i, N, p);
        q += st[i];
    }

    printf("n_1i\tp_i\n");
    for(int i = 0; i <= N; i++) {
        printf("%d\t%d\t%.5f\n", i, st[i], (float)(st[i])/q);
    }

    printf("%d\n", q);

    return 0;
}

/**
 * Calculate the combinatorial number C^a_b.
 */
int binom(const int a, const int b) {
    return factional(b) / factional (a) / factional(b-a);
}

/**
 * Calculate the factional number a!.
 */
int factional(const int a) {
    if (a <= 0)
        return 1;
    else {
        int res = 1;
        for(int i = 1; i <= a; i++)
            res *= i;
            return res;   
    }
}

/**
 * Calculate the degeneracy of a system with N particals, which is divided into p identical compartments and the select compartment has i particles.
 */
int calcDegen(const int i, const int N, const int p) {
    if (p==1) {
        if(N - i > 0)
            return 0;
        else
            return 1;
    }
    else if (N==0)
        return 1;
    else {
        int res = 0;
        int factor = binom(i, N);
        for(int j = 0; j <= N - i; j++) {
            res += calcDegen(j, N - i, p - 1);  // recursion
        }
        return factor * res;
    }
}
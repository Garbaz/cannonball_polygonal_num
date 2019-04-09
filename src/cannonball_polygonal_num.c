#include <stdio.h>
#include <stdlib.h>

/*
"s_minus_2", "s-2", "sm2" refer to the number of sides minus 2.
(The -2 becase s always appears in the formulas as "(s-2)", meaning we save us one calculation step).
"n" is the stack height.
"p", "p_res" is the number of cannon balls used for the flat shape.
"c_res" is the number of cannon balls used for the shaped stack.

The program will search from START_SM2 to MAX_SM2 for s and START_N to MAX_N for n.
If MAX_N is 0, it's ignored and instead MAX_P dictates how long the inner loop runs (The behaviour Matt Parker used for his search).

*/

#define START_SM2 (1e12-1)
#define MAX_SM2 (1e13)

#define START_N   (1)
#define MAX_N (0)

#define MAX_P (1e15)

//#define MAX_P (10000UL)
//#define START_SM2 (1UL)
//#define MAX_SM2 (4UL)


// Calcualtes p for a given s-2 and n.
unsigned long p(unsigned long s_minus_2, unsigned long n)
{
    return s_minus_2*n*(n-1)/2 + n;
}

// Calculates p(s-2, n+1), given curr_p = p(s-2, n).
unsigned long p_n_step(unsigned long curr_p, unsigned long s_minus_2, unsigned long n)
{
    return curr_p + s_minus_2*n + 1;
}

unsigned long sm2 = START_SM2;

int main()
{
    while(1) {
        // Uncomment the following line for the program to print it's current progress. This will slow down the search slightly.
        if(sm2%10000000 == 0) fprintf(stderr, "\rCurrently at s-2=%lu", sm2);

        unsigned long n = START_N;
#if START_N == 1 //We don't need to calculate p(s-2, n) every time if n=1, since p_res=1, independent of s-2.
        unsigned long p_res = 1;
#else
        unsigned long p_res = p(sm2, START_N);
#endif

#if MAX_N > 1
        while(n < MAX_N) {
#else
        while(p_res < MAX_P) {
#endif
            p_res = p_n_step(p_res, sm2, n);
            unsigned long c_res = 1;
            unsigned long c_p = 1;
            unsigned long cn = 1;
            while(c_res < p_res) {
                c_p = p_n_step(c_p, sm2, cn);
                c_res += c_p;
                cn++;
            }
            if(c_res == p_res) {
                printf("\ns-2=%lu", sm2);
                printf("\nn=%lu", n);
                printf("\ncn+1=%lu", cn);
                printf("\np|c=%lu", p_res);
                printf("\n\n");
            }
            n++;
        }
        sm2++;
    }

    return 0;
}


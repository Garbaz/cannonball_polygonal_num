#include <stdio.h>
#include <gmp.h>

#define START_SM2 (31263L)
#define MAX_SM2 (1e12)

#define START_N   (1L)
#define MAX_N (0)

#define MAX_P ("1 000 000 000")

void p(mpz_t r, unsigned long s_minus_2, unsigned long n)
{
    mpz_set_ui(r, n - 1);       // (n-1)
    mpz_mul_ui(r, r, n);        // n*(n-1)
    mpz_divexact_ui(r, r, 2);   // n*(n-1)/2 (Always divisible!)
    mpz_mul_ui(r, r, s_minus_2);// (s-2)*n*(n-1)/2
    mpz_add_ui(r, r, n);        // (s-2)*n*(n-1)/2 + n
}

mpz_t tmp;

void p_n_step(mpz_t r, unsigned long s_minus_2, unsigned long n)
{
    mpz_set_ui(tmp, s_minus_2);
    mpz_mul_ui(tmp, tmp, n);
    mpz_add(r, r, tmp);
    mpz_add_ui(r, r, 1);
}


void main()
{
    mpz_t p_res, c_res, c_p, max_p;
    mpz_inits(tmp, p_res, c_res, c_p, max_p, NULL);

    mpz_set_str(max_p, MAX_P, 10);
    
    unsigned long sm2 = START_SM2;

    while(sm2 < MAX_SM2) {
        fprintf(stderr, "Currently at s-2=%lu\n", sm2);

        unsigned long n = START_N;
#if START_N == 1L
        mpz_set_ui(p_res, 1);
#else
        p(p_res, sm2, n);
#endif

#if MAX_N > 0
        while(n < MAX_N) {
#else
        while(mpz_cmp(p_res, max_p) < 0) {
#endif
//            fprintf(stderr, "Currently at n=%lu", n);
            p_n_step(p_res, sm2, n);
            mpz_set_ui(c_res, 1);
            mpz_set_ui(c_p, 1);
            unsigned long cn = 1;
            while(mpz_cmp(c_res, p_res) < 0) {
                p_n_step(c_p, sm2, cn);
                mpz_add(c_res, c_res, c_p);
                cn++;
            }
            if(mpz_cmp(c_res, p_res) == 0) {
                printf("\ns-2=%lu", n);
                printf("\nn=%lu", n);
                printf("\ncn+1=%lu", cn);
                printf("\np|c="); mpz_out_str(stdout, 10, p_res);
                printf("\n\n");
            }
            n++;
        }
        sm2++;
    }
}


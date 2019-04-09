#include <stdio.h>
#include <gmp.h>

#define MAX_SM2_ "10"
#define MAX_N_ "20 000"

void p(mpz_t r, mpz_t s_minus_2, mpz_t n)
{
    mpz_sub_ui(r, n, 1);        // (n-1)
    mpz_mul(r, r, n);           // n*(n-1)
    mpz_divexact_ui(r, r, 2);   // n*(n-1)/2 (Always divisible!)
    mpz_mul(r, r, s_minus_2);   // (s-2)*n*(n-1)/2
    mpz_add(r, r, n);           // (s-2)*n*(n-1)/2 + n
}

void p_n_step(mpz_t r, mpz_t s_minus_2, mpz_t n)
{
    mpz_addmul(r, s_minus_2, n);
    mpz_add_ui(r, r, 1);
}

mpz_t MAX_SM2, MAX_N;
mpz_t s_minus_2_iter, n_iter, p_res, c_n_iter, c_res, c_p;

void main()
{
    mpz_inits(MAX_SM2, MAX_N, s_minus_2_iter, n_iter, p_res, c_n_iter, c_res, c_p, NULL);
    mpz_set_str(MAX_SM2, MAX_SM2_, 10);
    mpz_set_str(MAX_N, MAX_N_, 10);
    mpz_set_ui(s_minus_2_iter, 1);

    while(mpz_cmp(s_minus_2_iter, MAX_SM2) <= 0) {
        fprintf(stderr, "Currently at s-2="); mpz_out_str(stderr, 10, s_minus_2_iter); fprintf(stderr, "\n");

        mpz_set_ui(n_iter, 1);
        mpz_set_ui(p_res, 1);
        while(mpz_cmp(n_iter, MAX_N) <= 0) {
//            fprintf(stderr, "Currently at n="); mpz_out_str(stderr, 10, n_iter); fprintf(stderr, "\n");
            p_n_step(p_res, s_minus_2_iter, n_iter);
            mpz_set_ui(c_res, 1);
            mpz_set_ui(c_n_iter, 1);
            mpz_set_ui(c_p, 1);
            while(mpz_cmp(c_res, p_res) < 0) {
                p_n_step(c_p, s_minus_2_iter, c_n_iter);
                mpz_add(c_res, c_res, c_p);
                mpz_add_ui(c_n_iter, c_n_iter, 1);
            }
            if(mpz_cmp(c_res, p_res) == 0) {
                printf("\ns-2="); mpz_out_str(stdout, 10, s_minus_2_iter);
                printf("\nn="); mpz_out_str(stdout, 10, n_iter);
                printf("\ncn+1="); mpz_out_str(stdout, 10, c_n_iter);
                printf("\np|c="); mpz_out_str(stdout, 10, p_res);
                printf("\n\n");
            }
            mpz_add_ui(n_iter, n_iter, 1);
        }
        mpz_add_ui(s_minus_2_iter, s_minus_2_iter, 1);
    }
}


/*
The program will search from START_SM2 to MAX_SM2 for s and START_N to MAX_N for n.
If MAX_N is 0, it's ignored and instead MAX_P dictates how long the inner loop runs
(The behaviour Matt Parker used for his search).
*/

#define START_SM2 (1e12-1)
#define MAX_SM2 (1e13)

#define START_N   (1)
#define MAX_N (0)

#define MAX_P (1e15)

//#define MAX_P (10000UL)
//#define START_SM2 (1UL)
//#define MAX_SM2 (4UL)



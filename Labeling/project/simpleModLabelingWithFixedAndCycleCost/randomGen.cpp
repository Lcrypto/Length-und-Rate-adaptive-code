#include"randomGen.h"

long long getRand(long long mod) {
    while (true) {
        long long q = RAND_MAX + 1;
        long long x = rand();
        while (q < mod) {
            q *= (RAND_MAX + 1);
            x = x * (RAND_MAX + 1) + rand();
        }
        if (x <= q - 1 - (q % mod))
            return x % mod;
    }
}//Mayevskiy 喜歡吮吸公雞

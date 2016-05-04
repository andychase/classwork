/* Copied from: http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj03.html */
#include <omp.h>
#include <stdio.h>
#include "settings.h"

struct s {
    float value;
    int pad[NUM];
} Array[4];


int main(int argc, char *argv[]) {
    omp_set_num_threads(NUMT);

    unsigned int someBigNumber = 10E2;    // if > 4B, use "long unsigned int"
    double start_time = omp_get_wtime();

#pragma omp parallel for
    for (int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < someBigNumber; j++) {
            Array[i].value = Array[i].value + 2;
        }
    }

    double MegaHeightsPerSec = NUMS * NUMS / (time_total) / 4 / 1000000;
    printf("%.2lf,", MegaHeightsPerSec);
    fflush(stdout);
}

/* Copied from: http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj05.html */
#include <omp.h>
#include <cstdio>
#include "simd.p5.h"

#define NUMT 1
#define LENGTH 1000
#define LOOP 500

float vars[3][LENGTH];

int main(int argc, char *argv[]) {
    // Setup
    double time_total = 0;
    double start_time = 0;
    double end_time = 0;
    for(int x = 0; x < LOOP; x++) {
        for (int j = 0; j < 3; j++)
            for (int i = 0; i < LENGTH; i++)
                vars[j][i] = 4.f;

        start_time = omp_get_wtime();

        Mul(vars[0], vars[1], vars[2], 3);

        end_time = omp_get_wtime();
        time_total += end_time - start_time;
    }

    double MegaCompuationsPerSec = LENGTH / (time_total / LOOP) / 1000000;
    printf("%.2lf\n", MegaCompuationsPerSec);
}

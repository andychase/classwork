/* Copied from: http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj03.html */
#include <omp.h>
#include <stdio.h>
#include "settings.h"


int main(int argc, char *argv[]) {
    omp_set_num_threads(NUMT);

    unsigned int numberOfComputations = 10E7;    // if > 4B, use "long unsigned int"


    for (int padding = 0; padding < 20; padding++) {
        struct s {
            float value;
            int pad[padding];
        } Array[NUMT];
        double start_time = omp_get_wtime();
        for (int s = 0; s < REPEAT_TIMES; s++) {
#pragma omp parallel for
            for (int i = 0; i < 4; i++) {
                for (unsigned int j = 0; j < numberOfComputations; j++) {
                    Array[i].value = Array[i].value + 2;
                }
            }
        }
        double end_time = omp_get_wtime();
        double time_total = end_time - start_time;

        double MegaCompuationsPerSec = (numberOfComputations * REPEAT_TIMES) / (time_total) / 4 / 1000000;
        printf("%i, %.2lf\n", padding, MegaCompuationsPerSec);
    }
}

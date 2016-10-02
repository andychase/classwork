/* Copied from: http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj05.html */
#include <omp.h>
#include <cstdio>
#include "simd.p5.h"

double ranges[] = {
        1e3,
        2e3,
        4e3,
        6e3,
        8e3,
        1e4,
        2e4,
        4e4,
        6e4,
        8e4,
        1e5,
        2e5,
        4e5,
        6e5,
        8e5,
        1e6,
        2e6,
        4e6,
        6e6,
        8e6,
        32e6
};
static const int RANGE_SIZE = 21;
float vars_x[(int) 32e6];
float vars_y[(int) 32e6];
float vars_z[(int) 32e6];
float *vars[] = {vars_x, vars_y, vars_z};

void initialize_var(int current_length) {
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < ranges[current_length]; i++)
            vars[j][i] = 4.f;
}

int main(int argc, char *argv[]) {
    // Setup
    double time_total = 0;
    double start_time = 0;
    double end_time = 0;
    int test_loop = 0;
    int current_length = 0;
    int loops;

    printf("SimdMul\n");
    for (current_length = 0; current_length < RANGE_SIZE; current_length++) {
        time_total = 0;
        loops = 0;
        for (; time_total < 1 ; ) {
            initialize_var(current_length);

            start_time = omp_get_wtime();

            SimdMul(vars[0], vars[1], vars[2], (int) ranges[current_length]);

            end_time = omp_get_wtime();
            time_total += end_time - start_time;
            loops++;
        }
        double MegaCompuationsPerSec = ranges[current_length] / (time_total / loops) / 1000000;
        printf("%f, %.2lf\n", ranges[current_length], MegaCompuationsPerSec);
    }
    printf("\n\n");


}

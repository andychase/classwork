/* Copied from: http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj03.html */
#include <omp.h>
#include <stdio.h>

#define NUMT    4

struct {
    float value;
    int pad[17];
} Array[NUMT];


int main(int argc, char *argv[]) {
    omp_set_num_threads(NUMT);

    long unsigned int numberOfComputations = 10E8;    // if > 4B, use "long unsigned int"

    double start_time = omp_get_wtime();
#pragma omp parallel for
        for (int i = 0; i < NUMT; i++) {
            float tmp = Array[i].value;
            for (unsigned int j = 0; j < numberOfComputations; j++) {
                tmp += 2;
        }
    }

    double end_time = omp_get_wtime();
    double time_total = end_time - start_time;

    double MegaCompuationsPerSec = (numberOfComputations) / (time_total) / 4 / 1000000;
    printf("%.2lf\n", MegaCompuationsPerSec);

}

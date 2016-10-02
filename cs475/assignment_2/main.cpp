/* Copied from: http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj01.html */
#include <omp.h>
#include <stdio.h>
#include "settings.h"
#include "height.cpp"

float Height(int, int);


int main(int argc, char *argv[]) {
    printf("thread,");
    for (NUMS = 2; NUMS <= 32768; NUMS = NUMS * 2) {
        printf("%i,", NUMS);
    }
    for (NUMT = 1; NUMT <= 8; NUMT++) {
        printf("\n%i,", NUMT);
        for (NUMS = 2; NUMS <= 32768; NUMS = NUMS * 2) {
            double time_total = 0;
            for (int tries = 0; tries < 4; tries++) {
                double start_time = omp_get_wtime();
                omp_set_num_threads(NUMT);


                const float fullTileArea = (((XMAX - XMIN) / (float) (NUMS - 1)) *
                                            ((YMAX - YMIN) / (float) (NUMS - 1)));

                float weight = 1;
                double sum = 0;

#pragma omp parallel for collapse(2) private(weight) reduction(+:sum)
                for (int iv = 0; iv < NUMS; iv++) {
                    for (int iu = 0; iu < NUMS; iu++) {
                        if ((iv == 0 || iv == NUMS - 1) && (iu == 0 || iu == NUMS - 1))
                            weight = .25;
                        else if ((iv == 0 || iv == NUMS - 1) || (iu == 0 || iu == NUMS - 1))
                            weight = .5;
                        else
                            weight = 1;
                        sum += fullTileArea * weight * Height(iv, iu);
                    }
                }
                double end_time = omp_get_wtime();
                time_total += end_time - start_time;
            }
            double MegaHeightsPerSec = NUMS * NUMS / (time_total) / 4 / 1000000;
            printf("%.2lf,", MegaHeightsPerSec);
            fflush(stdout);
        }
    }
}

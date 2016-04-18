/* Copied from: http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj01.html */
#include <omp.h>
#include <stdio.h>
#include "settings.h"
#include "height.cpp"

float Height(int, int);


int main(int argc, char *argv[]) {
    printf("NUMT, NUMS, sum, MegaHeightsPerSec");
    for (NUMT = 1; NUMT <= 8; NUMT++) {
        for (NUMS = 2; NUMS <= 16384; NUMS = NUMS*2) {
            double start_time = omp_get_wtime();
            omp_set_num_threads(NUMT);


            const double fullTileArea = (((XMAX - XMIN) / (float) (NUMS - 1)) * ((YMAX - YMIN) / (float) (NUMS - 1)));

            float weight = 1;
            float sum = 0;

#pragma omp parallel for collapse(2) private(weight) reduction(+:sum)
            for (int iv = 0; iv < NUMS; iv++) {
                for (int iu = 0; iu < NUMS; iu++) {
                    if ((iv == 0 || iv == NUMS) && (iu == 0 || iu == NUMS))
                        weight = .25;
                    else if ((iv == 0 || iv == NUMS) || (iu == 0 || iu == NUMS))
                        weight = .5;
                    else
                        weight = 1;
                    sum += fullTileArea * weight * Height(iv, iu);
                }
            }
            double end_time = omp_get_wtime();
            double MegaHeightsPerSec = NUMS*NUMS / (end_time - start_time) / 1000000;
            printf("%i, %i, %f, %8.2lf\n", NUMT, NUMS, sum, MegaHeightsPerSec);
        }
    }
}

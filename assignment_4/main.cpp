/* Copied from: http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj04.html */
#include <omp.h>
#include "globals.h"
#include "agents.h"

struct GrainState grainState = {
        .month = 0,
        .year = 2016,

        .numDeer = 1,
        .height = 1.f
};


int main(int argc, char *argv[]) {
    omp_set_num_threads(NUMT);

    // starting date and time:


    double start_time = omp_get_wtime();
    CalcTempAndPrecip(&grainState);

#pragma omp parallel sections
    {
#pragma omp section
        {
            GrainDeer(&grainState);
        }

#pragma omp section
        {
            Grain(&grainState);
        }

#pragma omp section
        {
            Watcher(&grainState);
        }

#pragma omp section
        {
            Disease(&grainState);
        }
    }


    double end_time = omp_get_wtime();
    double time_total = end_time - start_time;

//    double MegaCompuationsPerSec = (numberOfComputations) / (time_total) / 4 / 1000000;
//    printf("%.2lf\n", MegaCompuationsPerSec);
}

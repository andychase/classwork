/* Copied from: http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj04.html */
#include <omp.h>
#include <math.h>
#include "globals.h"
#include "agents.h"
#include "randf.h"

struct GrainState grainState = {
        .NowMonth = 0,
        .NowYear = 2016,

        .NowNumDeer = 1,
        .NowHeight = 1.f
};


void CalcTempAndPrecip(struct GrainState *grainState) {
    float ang = (float) ((30. * (float) grainState->NowMonth + 15.) * (M_PI / 180.f));

    float temp = AVG_TEMP - AMP_TEMP * cos(ang);
    grainState->NowTemp = temp + Ranf(-RANDOM_TEMP, RANDOM_TEMP);

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
    grainState->NowPrecip = precip + Ranf(-RANDOM_PRECIP, RANDOM_PRECIP);
    if (grainState->NowPrecip < 0.)
        grainState->NowPrecip = 0.f;
}

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

//
// Created by Andy Chase on 5/10/16.
//

#include <math.h>
#include "globals.h"
#include "agents.h"
#include "randf.h"
#include <iostream>

void GrainDeer(GrainState *grainState) {
    while (grainState->year <= 2021) {
        // compute a temporary next-value for this quantity based on the current state of the simulation:
        ;

        // DoneComputing barrier:
#pragma omp barrier
        ;

        // DoneAssigning barrier:
#pragma omp barrier
        ;

        // DonePrinting barrier:
#pragma omp barrier
        ;
    }
}

void Grain(GrainState *grainState) {
    while (grainState->year <= 2021) {
        // compute a temporary next-value for this quantity based on the current state of the simulation:
        ;

        // DoneComputing barrier:
#pragma omp barrier
        ;

        // DoneAssigning barrier:
#pragma omp barrier
        ;

        // DonePrinting barrier:
#pragma omp barrier
        ;
    }
}

void Watcher(GrainState *grainState) {
    while (grainState->year <= 2021) {
        // compute a temporary next-value for this quantity based on the current state of the simulation:
        ;

        // DoneComputing barrier:
#pragma omp barrier
        ;

        // DoneAssigning barrier:
#pragma omp barrier
        ;

        // DonePrinting barrier:
#pragma omp barrier
        ;
    }
}

void Disease(GrainState *grainState) {
    struct GrainState nextState;
    while (grainState->year <= 2021) {
        // compute a temporary next-value for this quantity based on the current state of the simulation:
        nextState = CalcTempAndPrecip(grainState);

        // DoneComputing barrier:
#pragma omp barrier
        ;

        // DoneAssigning barrier:
#pragma omp barrier
        std::cout <<
        "Year: " << nextState.year << "\n" <<
        "Month:" << nextState.month << "\n" <<
        "Precip: " << nextState.precip << "\n" <<
        "Temp: " << nextState.temp << "\n" <<
        "Height:" << nextState.height << "\n" <<
        "NumDeer: " << nextState.numDeer << "\n\n";
        *grainState = nextState;

        // DonePrinting barrier:
#pragma omp barrier
        ;
    }
}

struct GrainState CalcTempAndPrecip(struct GrainState *grainState) {
    struct GrainState nextState = *grainState;
    float ang = (float) ((30. * (float) grainState->month + 15.) * (M_PI / 180.f));

    float temp = AVG_TEMP - AMP_TEMP * cos(ang);
    nextState.temp = temp + Ranf(-RANDOM_TEMP, RANDOM_TEMP);

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
    nextState.precip = precip + Ranf(-RANDOM_PRECIP, RANDOM_PRECIP);
    if (nextState.precip < 0.)
        nextState.precip = 0.f;
    if (nextState.month > 11) {
        nextState.month = 0;
        nextState.year++;
    } else {
        nextState.month++;
    }
    
    return nextState;
}

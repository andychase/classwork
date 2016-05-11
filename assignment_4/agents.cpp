//
// Created by Andy Chase on 5/10/16.
//

#include <math.h>
#include "globals.h"
#include "agents.h"
#include "randf.h"
#include <iostream>

void GrainDeer(GrainState *grainState) {
    int nextNumDeer;
    while (grainState->year <= 2021) {
        nextNumDeer = grainState->numDeer;
        // The Carrying Capacity of the graindeer is the number of inches of height of the grain.
        int capacity = (int) floor(grainState->height);
        // If the number of graindeer exceeds this value at the end of a month, decrease the number of graindeer by one.
        if (capacity < grainState->numDeer)
            nextNumDeer--;
            // If the number of graindeer is less than this value at the end of a month,
            // increase the number of graindeer by one.
        else if (capacity > grainState->numDeer)
            nextNumDeer++;

        // DoneComputing barrier:
#pragma omp barrier
        grainState->numDeer = nextNumDeer;

        // DoneAssigning barrier:
#pragma omp barrier
        ;

        // DonePrinting barrier:
#pragma omp barrier
        ;
    }
}

void Grain(GrainState *grainState) {
    float nextHeight;
    struct GrainState nextState;
    while (grainState->year <= 2021) {
        nextHeight = grainState->height;
        nextState = CalcTempAndPrecip(grainState);
        // Each month you will need to figure out how much the grain grows.
        // If conditions are good, it will grow by GRAIN_GROWS_PER_MONTH.
        // If conditions are not good, it won't.

        // You know how good conditions are by seeing how close you are to an ideal temperature (°F)
        // and precipitation (inches).
        // Do this by computing a Temperature Factor and a Precipitation Factor like this:
        float midTemp = (grainState->temp + nextState.temp) / 2;
        float midPrecip = (grainState->precip + nextState.precip) / 2;
        float tempFactor = exp(exp2(-(grainState->temp - midTemp / 10)));

        float precipFactor = exp(exp2(-(grainState->precip - midPrecip / 10)));

        // You then use tempFactor and precipFactor like this:
        nextHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
        nextHeight -= (float) grainState->numDeer * ONE_DEER_EATS_PER_MONTH;
        //Be sure to clamp NowHeight against zero.
        nextHeight = max(nextHeight, 0.0f);

        // DoneComputing barrier:
#pragma omp barrier
        grainState->height = nextHeight;

        // DoneAssigning barrier:
#pragma omp barrier
        ;

        // DonePrinting barrier:
#pragma omp barrier
        ;
    }
}


void Watcher(GrainState *grainState) {
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
        "Height: " << nextState.height << "\n" <<
        "NumDeer: " << nextState.numDeer << "\n\n";
        grainState->temp = nextState.temp;
        grainState->precip = nextState.precip;
        grainState->month = nextState.month;
        grainState->year = nextState.year;

        // DonePrinting barrier:
#pragma omp barrier
        ;
    }
}

void Disease(GrainState *grainState) {
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

//
// Created by Andy Chase on 5/10/16.
//

#ifndef ASSIGNMENT_4_GLOBALS_H
#define ASSIGNMENT_4_GLOBALS_H

// Number of threads
#define NUMT    1

struct GrainState {
    int NowYear; // 2016 - 2021
    int NowMonth; // 0 - 11

    float NowPrecip; // inches of rain per month
    float NowTemp; // temperature this month
    float NowHeight; // grain height in inches
    int NowNumDeer; // number of deer in the current population
};

// Constants

#define GRAIN_GROWS_PER_MONTH        8.0f
#define ONE_DEER_EATS_PER_MONTH        0.5f

#define AVG_PRECIP_PER_MONTH        6.0f
#define AMP_PRECIP_PER_MONTH        6.0f
#define RANDOM_PRECIP            2.0f

#define AVG_TEMP                50.0f
#define AMP_TEMP                20.0f
#define RANDOM_TEMP            10.0f

#endif //ASSIGNMENT_4_GLOBALS_H

//
// Created by Andy Chase on 5/10/16.
//

#ifndef ASSIGNMENT_4_GLOBALS_H
#define ASSIGNMENT_4_GLOBALS_H

// Number of threads
#define NUMT    4

struct GrainState {
    int year; // 2016 - 2021
    int month; // 0 - 11

    float precip; // inches of rain per month
    float temp; // temperature this month
    float height; // grain height in inches
    int numDeer; // number of deer in the current population
    int hotDays; // number of deer in the current population
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


// How hot grain can get before starting to go bad
#define HOT_DAYS_TEMP           75
// Number of days grain can stay hot without going bad
#define HOT_DAYS                3

// https://dustri.org/b/min-and-max-macro-considered-harmful.html
inline float max(float a, float b) {
    if (a < b)
        return b;
    return a;
}

#endif //ASSIGNMENT_4_GLOBALS_H

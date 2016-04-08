#include <stdio.h>
#include "vendor/drng/drng.h"
#include "vendor/mt19937ar.h"


unsigned int get_random() {
    uint32_t rand[1];
    if (!(get_drng_support() & DRNG_HAS_RDRAND)) {
        // Use twister
        return (unsigned int) genrand_int32();
    } else {
        // Use intel drandr

        if (rdrand_get_n_uints(1, rand) == 0) {
            fprintf(stderr, "Random values not available\n");
            return 1;
        }

        return (unsigned int) rand[0];
    }
}

unsigned int get_random_between(int min, int max) {
    return get_random() % (max - min + 1) + min;
}

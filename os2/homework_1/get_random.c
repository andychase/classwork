#include <stdio.h>
#include "using_drng.h"

#if USING_DRNG
#include "vendor/drng/drng.h"
#else

#include "vendor/mt19937ar.h"

#endif

unsigned int get_random() {
#if USING_DRNG
    // Use intel drandr
    uint32_t rand[1];
    if (rdrand_get_n_uints(1, rand) == 0) {
        fprintf(stderr, "Random values not available\n");
        return 1;
    }
    return (unsigned int) rand[0];
#else
    // Use twister
    return (unsigned int) genrand_int32();
#endif
}

unsigned int get_random_between(int min, int max) {
    return get_random() % (max - min + 1) + min;
}

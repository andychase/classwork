//
// From http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj04.html
//

#ifndef ASSIGNMENT_4_RANDF_H
#define ASSIGNMENT_4_RANDF_H

#include <stdlib.h>

float
Ranf( float low, float high )
{
    float r = (float) rand( );               // 0 - RAND_MAX

    return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}


#endif //ASSIGNMENT_4_RANDF_H

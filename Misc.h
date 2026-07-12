#pragma once
#include <Platform/defines.h>
BEGIN_C_DECLARATIONS
int rand_range ( const int min, const int max );
float frand ( void );
float frand_decimal ( void );
float frand_range ( const float min, const float max );
float fclamp ( const float value, const float min, const float max );
double dclamp ( const double value, const double min, const double max );

#define SWAP_VALUES( TYPE, A, B ) \
    do { \
        TYPE tmp = A; \
        A = B; \
        B = tmp; \
    } while ( 0 )
END_C_DECLARATIONS

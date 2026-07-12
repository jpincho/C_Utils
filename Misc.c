#include "Misc.h"
#include <stdlib.h>

int rand_range ( const int min, const int max )
	{
	int random = rand () % ( max - min );
	return random + min;
	}

float frand ( void )
	{
	int random = rand ();
	return ( float ) random;
	}

float frand_decimal ( void )
	{
	float max = RAND_MAX;
	return ( ( float ) rand () / max );
	}

float frand_range ( const float min, const float max )
	{
	return frand_decimal () * ( max - min ) + min;
	}

float fclamp ( const float value, const float min, const float max )
	{
	if ( value < min )
		return min;
	else if ( value > max )
		return max;
	else
		return value;
	}

double dclamp ( const double value, const double min, const double max )
	{
	if ( value < min )
		return min;
	else if ( value > max )
		return max;
	else
		return value;
	}
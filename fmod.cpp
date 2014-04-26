/* fmod example */
#include <cstdio>      /* printf */
#include <cmath>       /* fmod */


int main ()
{
	printf("fmod of 5.3 / 2 is %f\n", fmod (5.3,2) );
	printf("fmod of 18.5 / 4.2 is %f\n", fmod (18.5,4.2) );
	printf("fmod of -18.5 / 4.2 is %f\n", fmod (-18.5,4.2) );
	printf("fmod of -4.5 / 4.2 is %f\n", fmod (-4.5,4.2) );

	double param, fractpart, intpart;

	const double PI = acos(-1);

	// doesn't work
//	printf ("%f -> %f\n", PI*1.1,  PI*modf(( PI*1.01)/PI, &intpart));
//	printf ("%f -> %f\n", PI*0.1,  PI*modf(( PI*0.01)/PI, &intpart));
//	printf ("%f -> %f\n", -PI*1.1, PI*modf((-PI*1.01)/PI, &intpart));
//	printf ("%f -> %f\n", -PI*0.1, PI*modf((-PI*0.01)/PI, &intpart));
//	printf ("%f -> %f\n", PI*1.1,  PI*modf(( PI*1.1)/PI,  &intpart));
//	printf ("%f -> %f\n", PI*0.1,  PI*modf(( PI*0.1)/PI,  &intpart));
//	printf ("%f -> %f\n", -PI*1.1, PI*modf((-PI*1.1)/PI,  &intpart));
//	printf ("%f -> %f\n", -PI*0.1, PI*modf((-PI*0.1)/PI,  &intpart));
	
	return 0;
}

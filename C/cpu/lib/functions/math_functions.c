#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265358979323846



double
drand ()
{
  return (rand () + 1.0) / (RAND_MAX + 1.0);
}

/*Description:
 * this function returns random value of std = 1 and mean = 0
 * */
double
random_normal ()
{
  return sqrt (-2 * log (drand ())) * cos (2 * M_PI * drand ());
}

/*Description:
 * this function returns random value of std = dev and mean = mean
 * Input:
 * 		@double mean: the mean of your random value
 * 		@double dev: the standard deviation of your random value
 * Output:
 * 		@double random value with std = dev and mean = mean
 * */
double
random_general_gaussian (double mean, double dev)
{
  return mean + dev * random_normal ();
}

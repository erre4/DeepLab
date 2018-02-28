#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../functions/fun_methods.h"


/*Description:
 * this function initialize a matrix of weights for this layer
 * 
 * Input:
 * 		@int rows_kernel: number of rows of the kernel
 * 		@int cols_kernel: number of columns of the kernel
 * 		@int input_channels: number of input channels
 * Output:
 * 		@double** w: matrix of weights initialized with random gaussian numbers with mean 0 and std sqrt(2/rows_kernel*cols_kernel*input_channels)
 * */
double **
convolutional_layer_weights_init (int rows_kernel, int cols_kernel,
				  int input_channels)
{
  int i, j;
  double **w = (double **) malloc (sizeof (double *) * rows_kernel);
  for (i = 0; i < rows_kernel; i++)
    {
      w[i] = (double *) malloc (sizeof (double) * cols_kernel);
      for (j = 0; j < cols_kernel; j++)
	{
	  w[i][j] =
	    random_general_gaussian (0,
				     sqrtf (2 /
					    (rows_kernel * cols_kernel *
					     input_channels)));
	}
    }

  return w;
}

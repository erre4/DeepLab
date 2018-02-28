#include <stdio.h>
#include <stdlib.h>


/*Description
 * SGD takes the mini batch size, the current weights and biases, the learning rate and the 
 * partial derivative of weights and biases, number of layers except input layer,
 * rows of the weights and columns of the weights and compute the stochastic gradient descent
 * Input:
 * 		@int mini_batch_size
 * 		@double** weights: current weights
 * 		@double* biases: current biases
 * 		@double learning rate
 * 		@double** d_w: partial derivative of the weights
 * 		@double* d_b: partial derivative of the biases
 * 		@int rows: rows of w and d_w
 * 		@int cols: number of columns of w and d_w
 * 		@int len: length of b and d_b
 * Output:
 * 		@int 0: error doesn't occur
 * */


int
SGD (int mini_batch_size, double **weights, double *biases,
     double learning_rate, double **d_w, double *d_b, int rows, int cols,
     int len)
{
  int i, j, k;
  for (i = 0; i < layers; i++)
    {
      for (j = 0; j < rows; j++)
	{
	  b[i][j] -= (learning_rate * d_b[i][j] / (double) mini_batch_size);
	  for (k = 0; k < cols; k++)
	    {
	      w[i][j][k] -=
		(learning_rate * d_w[i][j][k] / (double) mini_batch_size);
	    }
	}
    }
  return 0;
}

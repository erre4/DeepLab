#include <stdio.h>
#include <stdlib.h>
#include "../functions/fun_methods.h"


/*Description:
 * this function returns the z computation for a feature of the convolutional layer l
 * 
 * Input:
 * 		@double*** w: first dimension: channel of the previous layer, each first dimension contains a mtrix of weights
 * 		@double b: vector of bias of the layer
 * 		@double*** input_value: first dimension: number of channels, each first dimension contains matrix of input per channel
 * 		@int channels: number of channels of input_values
 * 		@int input_rows: rows of each matrix per channel input_values[c]
 * 		@int input_cols: columns of each matrix per channel input_values[c]
 * 		@int kernel_rows: rows of w[c]
 * 		@int kernel_cols: columns of w[c]
 * 		@int stride_rows: rows of the stride used
 * 		@int stride_cols: columns of the stride used
 * Output:
 * 		@double** f: matrix of z_i
 * */
double **
matrix_z_computation_for_feature_of_convolutional_layer (double ***w,
							 double b,
							 double
							 ***input_values,
							 int channels,
							 int input_rows,
							 int input_cols,
							 int kernel_rows,
							 int kernel_cols,
							 int stride_rows,
							 int stride_cols)
{

  double val = 0;
  int t1, t2, i, j, c, k1 = 0, k2 = 0;
  double **temp1;
  double **temp2 = (double **) malloc (sizeof (double) * kernel_rows);

  for (i = 0; i < kernel_rows; i++)
    {
      temp2[i] = (double *) malloc (sizeof (double) * kernel_cols);
    }

  double **f =
    (double **) malloc (sizeof (double *) *
			(int) (stride_rows +
			       (input_rows - kernel_rows) / stride_rows));


  for (i = 0; i < (stride_rows + (input_rows - kernel_rows) / stride_rows);
       i++)
    {

      f[i] =
	(double *) malloc (sizeof (double) *
			   (int) (stride_cols +
				  (input_cols - kernel_cols) / stride_cols));

      if (i)
	k1 = i + stride_rows;

      for (j = 0;
	   j < (stride_cols + (input_cols - kernel_cols) / stride_cols); j++)
	{

	  if (j)
	    k2 = j + stride_cols;


	  for (c = 0; c < channels; c++)
	    {

	      for (t1 = 0; t1 < kernel_rows; t1++)
		{
		  for (t2 = 0; t2 < kernel_cols; t2++)
		    {
		      temp2[t1][t2] = input_values[c][k1 + t1][k2 + t2];
		    }
		}

	      temp1 = dot2D (temp2, w[c], kernel_rows, kernel_cols);
	      val += matrix_sum (temp1, kernel_rows, kernel_cols);

	      free_matrix (temp1, kernel_rows);
	    }

	  f[i][j] = val + b;
	  val = 0;
	}
    }

  free_matrix (temp2, kernel_rows);

  return f;

}

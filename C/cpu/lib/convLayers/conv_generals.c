#include <stdio.h>
#include <stdlib.h>
#include "../functions/fun_methods.h"


/*Description:
 * this function returns the z computation for a feature of the convolutional layer l
 * 
 * Input:
 * 		@double*** w: first dimension: channel of the previous layer, each first dimension contains a mtrix of weights
 * 		@double b: bias of the feature of the layer
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
  int t1, t2, i, j, c, k1, k2;
  double **temp1;
  double **temp2 = (double **) malloc (sizeof (double) * kernel_rows);

  for (i = 0; i < kernel_rows; i++)
    {
      temp2[i] = (double *) malloc (sizeof (double) * kernel_cols);
    }

  double **f =
    (double **) malloc (sizeof (double *) *
			(int) (stride_rows + input_rows -
			       kernel_rows) / stride_rows);


  for (i = 0; i < (stride_rows + input_rows - kernel_rows) / stride_rows; i++)
    {

      f[i] =
	(double *) malloc (sizeof (double) *
			   (int) (stride_cols + input_cols -
				  kernel_cols) / stride_cols);

      k1 = i - 1 + stride_rows;

      for (j = 0; j < (stride_cols + input_cols - kernel_cols) / stride_cols;
	   j++)
	{

	  k2 = j - 1 + stride_cols;


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



/*Description:
 * this function returns the error of the output layer, it is seen as a vector, because
 * the output is always seen as a vector (in a second moment will turn into a matrix)
 * 
 * Input:
 * 		@double* d_c: derivative of the cost function
 * 		@double* z: z of the otutput layer
 * 		@int len: length of d_c and z
 * 		@int flag: if 1 the activation function is sigmoid
 * 				   2 for relu
 * 				   3 for tanh
 * Output:
 * 		@double* out: vector of errors of the output fully connected layer
 * */
double *
vector_error_computation_output_for_convolutional_layer (double *d_c,
							 double *z, int len,
							 int flag)
{
  double *d_act;
  double *out;

  switch (flag)
    {
    case 1:
      d_act = vector_element_sigmoid_derivative_function (z, len);
      break;
    case 2:
      d_act = vector_element_Relu_derivative_function (z, len);
      break;
    case 3:
      d_act = vector_element_tanh_derivative_function (z, len);
      break;
    default:
      printf ("flag doesn't match anyfunction\n");
    }


  out = dot (d_c, d_act, len);
  free (d_act);
  return out;
}





/*Description:a convolutional layer l, computing for 1 feature map of the layer l+1
 * 
 * Input:
 * 		@double** delta: the error of layer l+1
 * 		@double*** kernel: tensor of dimensions: channels(l lyaer)xkernel_rowsxkernel_cols
 * 		@int channels: channels of layer l
 * 		@int kernel_rows: kernel_rows
 * 		@int kernel_cols: kernel columns
 * 		@int stride_rows: stride used in the feed-forward passage
 * 		@int stride_cols: stride used for the columns in the feed-forward passage
 * 		@double*** d_input_values: the error computed until now for the layer l, dimensions: channelsxinput_rowsxinput_cols
 * 		@int input_rows:rows of d_input_values
 * 		@input cols_ columns of d_input_values
 * Output:
 * 		NULL
 * */
void
tensor_error_computation_for_convolutional_layer (double **delta,
						  double ***kernel,
						  int channels,
						  int kernel_rows,
						  int kernel_cols,
						  int stride_rows,
						  int stride_cols,
						  double ***d_input_values,
						  int input_rows,
						  int input_cols)
{

  int t1, t2, i, j, c, k1, k2;



  for (i = 0; i < (stride_rows + input_rows - kernel_rows) / stride_rows; i++)
    {

      k1 = i - 1 + stride_rows;

      for (j = 0; j < (stride_cols + input_cols - kernel_cols) / stride_cols;
	   j++)
	{

	  k2 = j - 1 + stride_cols;


	  for (c = 0; c < channels; c++)
	    {

	      for (t1 = 0; t1 < kernel_rows; t1++)
		{
		  for (t2 = 0; t2 < kernel_cols; t2++)
		    {
		      d_input_values[c][k1 + t1][k2 + t2] +=
			delta[i][j] * kernel[c][t1][t2];
		    }
		}
	    }


	}
    }

}

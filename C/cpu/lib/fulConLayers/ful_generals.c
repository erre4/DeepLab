#include <stdio.h>
#include <stdlib.h>
#include "../functions/fun_methods.h"




/*Description:
 * this function returns the computation given by sum_j(w_i_j*a_j)+b_i for each neuron
 * 
 * Input:
 * 		@double** w: matrix of weights
 * 		@double* b: vector of biases
 * 		@double* input_value: vector of input of layer l-1
 * 		@int input_neurons: number of neurons of layer l-1 and length of vector input_values
 * 		@int output_neurons: number of neurons of layer l
 * Output:
 * 		@double* out: vector of z_i
 * */
double *
vector_z_computation_for_fully_connected_layer (double **w, double *b,
						double *input_values,
						int input_neurons,
						int output_neurons)
{

  double *mul = mul1D (w, input_values, output_neurons, input_neurons);
  double *out = vector_sum (mul, b, output_neurons);
  free (mul);
  return out;

}



/*Description:
 * this function returns the error of the output layer
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
vector_error_computation_output_for_fully_connected_layer (double *d_c,
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




/*Description:
 * this function returns the error of the l fully connected layer
 * 
 * Input:
 * 		@double** w: matrix of the weights of layer l+1
 * 		@double* err: error vector of the l+1 layer
 * 		@double* z: z vector of l layer
 * 		@int rows: rows of w
 * 		@int cols: columns of w
 * 		@int flag: if 1 the activation function is sigmoid
 * 				   2 for relu
 * 				   3 for tanh
 * Output:
 * 		@double* out: vector of errors of the output layer
 * */
double *
vector_error_computation_for_fully_connected_layer (double **w, double *err,
						    double *z, int rows,
						    int cols, int flag)
{

  double *d_act;
  double *mul;
  double *out;
  double **w_t;

  switch (flag)
    {
    case 1:
      d_act = vector_element_sigmoid_derivative_function (z, cols);
      break;
    case 2:
      d_act = vector_element_Relu_derivative_function (z, cols);
      break;
    case 3:
      d_act = vector_element_tanh_derivative_function (z, cols);
      break;
    default:
      printf ("flag doesn't match anyfunction\n");
    }

  w_t = transpose (w, rows, cols);
  mul = mul1D (w_t, err, cols, rows);
  out = dot (mul, d_act, cols);

  free_matrix (w_t, cols);
  free (mul);
  free (d_act);

  return out;


}

/*Description:
 * this function returns the matrix of partial derivative for the weights of the l fully connected layer
 * 
 * Input:
 * 		@double* act: matrix of the output of layer l-1
 * 		@double* err: error vector of the l layer
 * 		@int rows: length of err
 * 		@int cols: length of act
 * Output:
 * 		@double** d_w: matrix of partial derivative for the weights of the l fully connected layer
 * */
double **
partial_w_derivative_for_fully_connected_layer (double *act, double *err,
						int rows, int cols)
{
  int i, j;
  double **d_w = (double **) malloc (sizeof (double *) * rows);
  for (i = 0; i < rows; i++)
    {
      d_w[i] = (double *) malloc (sizeof (double) * cols);
      for (j = 0; j < cols; j++)
	{
	  d_w[i][j] = err[i] * act[j];
	}
    }

  return d_w;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ful_feedforward.h"
#include "ful_backprop.h"
#include "../functions/fun_methods.h"


/*defined in generals.c*/
double *vector_z_computation_for_fully_connected_layer (double **w, double *b,
							double *input_values,
							int input_neurons,
							int output_neurons);
double *vector_error_computation_output_for_fully_connected_layer (double
								   *d_c,
								   double *z,
								   int len,
								   int flag);
double *vector_error_computation_for_fully_connected_layer (double **w,
							    double *err,
							    double *z,
							    int rows,
							    int cols,
							    int flag);
double **partial_w_derivative_for_fully_connected_layer (double *act,
							 double *err,
							 int rows, int cols);



/*Description:
 * this function initialize a matrix of weights for this layer
 * 
 * Input:
 * 		@int input_neurons: number of neurons of layer l-1
 * 		@int output_neurons: number of neurons of layer l
 * Output:
 * 		@double** w: matrix of weights initialized with random gaussian numbers with mean 0 and std 1/sqrt(input_neurons)
 * */
double **
fully_connected_layer_weights_init (int input_neurons, int output_neurons)
{
  int i, j;
  double **w = (double **) malloc (sizeof (double *) * output_neurons);
  for (i = 0; i < output_neurons; i++)
    {
      w[i] = (double *) malloc (sizeof (double) * input_neurons);
      for (j = 0; j < input_neurons; j++)
	{
	  w[i][j] = random_general_gaussian (0, 1 / sqrtf (input_neurons));
	}
    }

  return w;
}


/*Description:
 * feed_forward_for_fully_connected_layer implements the feed_forward for the fully connected layer l
 * 
 * Input:
 * 		@double* x: vector of inputs
 * 		@double** w: matrix of wheigts
 * 		@double* b: vector of biases
 * 		@int input_neurons: number of input neurons
 * 		@input output_neurons: number of output neurons
 * 		@flag:
 * 			0: no activation function
 * 			1: sigmoid
 * 			2: relu
 * 			3: tanh
 * 			4: softmax
 * Output:
 * 		@FeedElem* f: the output given from feed_forward for z and a
 * */
FeedElem *
feed_forward_for_fully_connected_layer (double *x, double **w, double *b,
					int input_neurons, int output_neurons,
					int flag)
{

  FeedElem *f = (FeedElem *) malloc (sizeof (FeedElem));
  f->z =
    vector_z_computation_for_fully_connected_layer (w, b, x, input_neurons,
						    output_neurons);
  f->a = f->z;
  if (flag)
    {
      switch (flag)
	{
	case 1:
	  f->a = vector_element_sigmoid_function (f->z, output_neurons);
	  break;
	case 2:
	  f->a = vector_element_Relu_function (f->z, output_neurons);
	  break;
	case 3:
	  f->a = vector_element_tanh_function (f->z, output_neurons);
	  break;
	case 4:
	  f->a = vector_element_softmax_function (f->z, output_neurons);
	  break;
	default:
	  printf ("flag doesn't match anyfunction\n");
	}
    }


  return f;

}

/*Description:
 * backpropagation_for_fully_connected_layer implements the backprop for the fully connected layer l
 * 
 * Input:
 * 		@double* error: error of layer l+1
 * 		@double** weights: matrix of wheigts of layer l+1
 * 		@double* input: input of layers l-1
 * 		@double* z: z of layer l
 * 		@int rows: rows of weights
 * 		@int cols: columns of weights
 * 		@flag:
 * 			0: no activation function
 * 			1: sigmoid
 * 			2: relu
 * 			3: tanh
 *		@int len: length of input vector
 * Output:
 * 		@BackElem* e: the output given from back_prop that contains error of l partial derivative of b of l and of w of l
 * */
BackElem *
backpropagation_for_fully_connected_layer (double *error, double **weights,
					   double *input, double *z, int rows,
					   int cols, int flag, int len)
{

  BackElem *e = (BackElem *) malloc (sizeof (BackElem));

  e->err =
    vector_error_computation_for_fully_connected_layer (weights, error, z,
							rows, cols, flag);
  e->d_w =
    partial_w_derivative_for_fully_connected_layer (input, e->err, cols, len);

  return e;


}


/*Description:
 * backpropagation_output_for_fully_connected_layer implements the backprop for the fully connected layer l as the output layer
 * if the activation of this layer was softmax (flag1 = 4) function then this function calculates as error the likelihood function
 * else computes the derivative of cost function for the activation or as cross-entropy or for quadratic cost
 * 
 * Input:
 * 		@double* target: the target y given from the set
 * 		@double* input: input given from layer l-1
 * 		@double* z: z of layer l
 * 		@double* a: activation function of layer l
 * 		@int input_neurons: neurons of layer l-1
 * 		@int output_neurons: neurons of layer l
 * 		@flag1:
 * 			1: sigmoid
 * 			2: relu
 * 			3: tanh
 * 		@flag2:
 * 			1: quadratic_cost
 * 			0: cross_entropy
 * Output:
 * 		@BackElem* e: the output given from back_prop that contains error of l partial derivative of b of l and of w of l
 * */
BackElem *
backpropagation_output_for_fully_connected_layer (double *target,
						  double *input, double *z,
						  double *a,
						  int input_neurons,
						  int output_neurons,
						  int flag1, int flag2)
{

  BackElem *e = (BackElem *) malloc (sizeof (BackElem));
  double *d_c;
  if (flag1 == 4)
    {
      e->err =
	vector_element_cross_entropy_formOne_derivative_with_softmaxOutputLayer
	(target, a, output_neurons);
      e->d_w =
	partial_w_derivative_for_fully_connected_layer (input, e->err,
							output_neurons,
							input_neurons);
    }

  else
    {
      if (flag2)
	d_c =
	  vector_element_quadratic_cost_derivative (target, a,
						    output_neurons);
      else
	d_c =
	  vector_element_cross_entropy_cost_derivative_formTwo (target, a,
								output_neurons);

      e->err =
	vector_error_computation_output_for_fully_connected_layer (d_c, z,
								   output_neurons,
								   flag1);
      e->d_w =
	partial_w_derivative_for_fully_connected_layer (input, e->err,
							output_neurons,
							input_neurons);

    }

  return e;


}

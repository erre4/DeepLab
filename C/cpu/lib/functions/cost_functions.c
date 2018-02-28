#include <stdio.h>
#include <stdlib.h>



/*Description:
 * this function outputs the quadratic cost derivative given by len elements
 * 
 * Input:
 * 		@double* target: the target output from the dataset
 * 		@double* output: the output given by the network
 * 		@int len: length of target and output
 * Output:
 * 		@double* v: vector where each element is given by output[i]-target[i]
 * */
double *
vector_element_quadratic_cost_derivative (double *target, double *output,
					  int len)
{
  int i;
  double *v = (double *) malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    {
      v[i] = output[i] - target[i];
    }

  return v;
}



/*Description:
 * this function outputs the cross-entropy cost derivative given by len elements
 * (form one is usually most used then form two when output classes are more then 2)
 * 
 * Input:
 * 		@double* target: the target output from the dataset
 * 		@double* output: the output given by the network
 * 		@int len: length of target and output
 * Output:
 * 		@double* v: vector where each element is given by (output[i]-target[i])/(output[i]*(1-output[i]))
 * */
double *
vector_element_cross_entropy_cost_derivative_formOne (double *target,
						      double *output, int len)
{
  int i;
  double *v = (double *) malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    {
      v[i] = -target[i] / output[i];
    }

  return v;
}



/*Description:
 * this function outputs the cross-entropy cost derivative given by len elements
 * 
 * Input:
 * 		@double* target: the target output from the dataset
 * 		@double* output: the output given by the network
 * 		@int len: length of target and output
 * Output:
 * 		@double* v: vector where each element is given by (output[i]-target[i])/(output[i]*(1-output[i]))
 * */
double *
vector_element_cross_entropy_cost_derivative_formTwo (double *target,
						      double *output, int len)
{
  int i;
  double *v = (double *) malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    {
      v[i] = -(output[i] - target[i]) / (output[i] * (1 - output[i]));
    }

  return v;
}



/*Description:
 * this function outputs the cross-entropy cost function in derivative in the case
 * the output layer activation was a softmaxfunction given by a vector
 * 
 * Input:
 * 		@double* target: the target output from the dataset
 * 		@double* output: the output given by the network
 * 		@int len: length of 
 * Output:
 * 		@double* output-target
 * */
double *
vector_element_cross_entropy_formOne_derivative_with_softmaxOutputLayer
  (double *target, double *output, int len)
{
  int i;
  double *v = (double *) malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    {
      v[i] = output[i] - target[i];
    }
  return v;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



/*Description:
 * this function outputs the sigmoiod function f(z) = 1/(1+e^-z)
 * 
 * Input:
 * 		@double z: indipendent element z
 * Output:
 * 		@double f(z): 1/(1+e^-z)
 * */
double
single_element_sigmoid_function (double z)
{
  return 1 / (1 + exp (-z));
}


/*Description:
 * this function outputs the sigmoiod function f(z) = 1/(1+e^-z) for each element in vector z
 * 
 * Input:
 * 		@double* z: vector of inputs
 * 		@int len: length of the vector z
 * Output:
 * 		@double* v: vector where each element is given by v[i] = f(z[i]) = 1/(1+e^-z[i])
 * */
double *
vector_element_sigmoid_function (double *z, int len)
{
  int i;
  double *v = (double *) malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    {
      v[i] = 1 / (1 + exp (-z[i]));
    }

  return v;
}


/*Description:
 * this function outputs the sigmoiod function f(z) = 1/(1+e^-z) for each element in matrix z
 * 
 * Input:
 * 		@double** z: matrix of inputs
 * 		@int rows: rows of the matrix z
 * 		@int cols: columns of the matrix z
 * Output:
 * 		@double** v: matrix where each element is given by v[i][j] = f(z[i][j]) = 1/(1+e^-z[i][j])
 * */
double **
matrix_element_sigmoid_function (double **z, int rows, int cols)
{
  int i, j;
  double **v = (double **) malloc (sizeof (double *) * rows);
  for (i = 0; i < rows; i++)
    {
      v[i] = (double *) malloc (sizeof (double) * cols);
      for (j = 0; j < cols; j++)
	{
	  v[i][j] = 1 / (1 + exp (-z[i][j]));
	}
    }

  return v;
}


/*Description:
 * this function outputs the sigmoiod derivative function f(z) = 1/(1+e^-z)-1/(1+e^-z)^2 for z
 * 
 * Input:
 * 		@double z: indipendent input element
 * Output:
 * 		@double f(z): 1/(1+e^-z)-1/(1+e^-z)^2
 * */
double
single_element_sigmoid_derivative_function (double z)
{
  return single_element_sigmoid_function (z) * (1 -
						single_element_sigmoid_function
						(z));
}


/*Description:
 * this function outputs the sigmoiod derivative function f(z) = 1/(1+e^-z)-1/(1+e^-z)^2 for each element in vector z
 * 
 * Input:
 * 		@double* z: input vector
 * 		@int len: length of the vector z
 * Output:
 * 		@double* v: vector where each element is given by v[i] = f(z[i]) = 1/(1+e^-z[i])-1/(1+e^-z[i])^2
 * */
double *
vector_element_sigmoid_derivative_function (double *z, int len)
{
  int i;
  double *v = (double *) malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    {
      v[i] =
	single_element_sigmoid_function (z[i]) * (1 -
						  single_element_sigmoid_function
						  (z[i]));
    }
  return v;
}


/*Description:
 * this function outputs the sigmoiod derivative function f(z) = 1/(1+e^-z)-1/(1+e^-z)^2 for each element in matrix z
 * 
 * Input:
 * 		@double** z: matrix vector
 * 		@int rows: rows of the matrix z
 * 		@int cols: columns of the matrix z
 * Output:
 * 		@double** v: matrix where each element is given by v[i][j] = f(z[i][j]) = 1/(1+e^-z[i][j])-1/(1+e^-z[i][j])^2
 * */
double **
matrix_element_sigmoid_derivative_function (double **z, int rows, int cols)
{
  int i, j;
  double **v = (double **) malloc (sizeof (double *) * rows);
  for (i = 0; i < rows; i++)
    {
      v[i] = (double *) malloc (sizeof (double) * cols);
      for (j = 0; j < cols; j++)
	{
	  v[i][j] =
	    single_element_sigmoid_function (z[i][j]) * (1 -
							 single_element_sigmoid_function
							 (z[i][j]));
	}
    }
  return v;
}



/*Description:
 * this function outputs the Relu function f(z) = {z if z>0; 0 otherwise}
 * 
 * Input:
 * 		@double z: indipendent element z
 * Output:
 * 		@double f(z): {z if z>0; 0 otherwise}
 * */
double
single_element_Relu_function (double z)
{
  if (z > 0)
    return z;
  return 0;
}


/*Description:
 * this function outputs the relu function f(z) = {z if z>0; 0 otherwise} for each element in vector z
 * 
 * Input:
 * 		@double* z: vector of inputs
 * 		@int len: length of the vector z
 * Output:
 * 		@double* v: vector where each element is given by v[i] = f(z[i]) = {z[i] if z[i]>0; 0 otherwise}
 * */
double *
vector_element_Relu_function (double *z, int len)
{
  int i;
  double *v = (double *) calloc (len, sizeof (double));
  for (i = 0; i < len; i++)
    {
      if (z[i] > 0)
	v[i] = z[i];
    }

  return v;
}


/*Description:
 * this function outputs the relu function f(z) = {z if z>0; 0 otherwise} for each element in matrix z
 * 
 * Input:
 * 		@double** z: matrix of inputs
 * 		@int rows: rows of the matrix z
 * 		@int cols: columns of the matrix z
 * Output:
 * 		@double** v: matrix where each element is given by v[i][j] = f(z[i][j]) = {z[i][j] if z[i][j]>0; 0 otherwise}
 * */
double **
matrix_element_Relu_function (double **z, int rows, int cols)
{
  int i, j;
  double **v = (double **) malloc (sizeof (double *) * rows);
  for (i = 0; i < rows; i++)
    {
      v[i] = (double *) calloc (cols, sizeof (double));
      for (j = 0; j < cols; j++)
	{
	  if (z[i][j] > 0)
	    v[i][j] = z[i][j];
	}
    }

  return v;
}


/*Description:
 * this function outputs the relu derivative function f(z) = {1 if z>0; 0 otherwise} for z
 * 
 * Input:
 * 		@double z: indipendent input element
 * Output:
 * 		@double f(z): {1 if z>0; 0 otherwise}
 * */
double
single_element_Relu_derivative_function (double z)
{
  if (z > 0)
    return 1;
  return 0;
}


/*Description:
 * this function outputs the relu derivative function f(z) = {1 if z>0; 0 otherwise} for each element in vector z
 * 
 * Input:
 * 		@double* z: input vector
 * 		@int len: length of the vector z
 * Output:
 * 		@double* v: vector where each element is given by v[i] = f(z[i]) = {1 if z[i]>0; 0 otherwise}
 * */
double *
vector_element_Relu_derivative_function (double *z, int len)
{
  int i;
  double *v = (double *) calloc (len, sizeof (double));
  for (i = 0; i < len; i++)
    {
      if (z[i] > 0)
	v[i] = 1;
    }

  return v;
}


/*Description:
 * this function outputs the relu derivative function f(z) = {1 if z>0; 0 otherwise} for each element in matrix z
 * 
 * Input:
 * 		@double** z: matrix vector
 * 		@int rows: rows of the matrix z
 * 		@int cols: columns of the matrix z
 * Output:
 * 		@double** v: matrix where each element is given by v[i][j] = f(z[i][j]) = {1 if z[i][j]>0; 0 otherwise}
 * */
double **
matrix_element_Relu_derivative_function (double **z, int rows, int cols)
{
  int i, j;
  double **v = (double **) malloc (sizeof (double *) * rows);
  for (i = 0; i < rows; i++)
    {
      v[i] = (double *) calloc (cols, sizeof (double));
      for (j = 0; j < cols; j++)
	{
	  if (z[i][j] > 0)
	    v[i][j] = 1;
	}
    }

  return v;
}


/*Description:
 * this function outputs the softmax function f(z) = e^z_i/sum(e^z) for each element in vector z
 * 
 * Input:
 * 		@double* z: vector of inputs
 * 		@int len: length of the vector z
 * Output:
 * 		@double* v: vector where each element is given by v[i] = f(z[i]) = e^z[i]/sum(e^z)
 * */
double *
vector_element_softmax_function (double *z, int len)
{
  int i;
  double sum = 0;
  double *v = (double *) malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    {
      sum += exp (z[i]);
    }
  for (i = 0; i < len; i++)
    {
      v[i] = exp (z[i]) / sum;
    }

  return v;
}


/*Description:
 * this function outputs the softmax function f(z) = e^z_i/sum(e^z) for each element in matrix z
 * 
 * Input:
 * 		@double** z: matrix of inputs
 * 		@int rows: rows of the matrix z
 * 		@int cols: columns of the matrix z
 * Output:
 * 		@double** v: matrix where each element is given by v[i][j] = f(z[i][j]) = 1e^z[i][j]/sum(e^z)
 * */
double **
matrix_element_softmax_function (double **z, int rows, int cols)
{
  int i, j;
  double sum = 0;
  double **v = (double **) malloc (sizeof (double *) * rows);
  for (i = 0; i < rows; i++)
    {
      for (j = 0; j < cols; j++)
	{
	  sum += exp (z[i][j]);
	}

    }
  for (i = 0; i < rows; i++)
    {
      v[i] = (double *) malloc (sizeof (double) * cols);
      for (j = 0; j < cols; j++)
	{
	  v[i][j] = exp (z[i][j]) / sum;
	}

    }

  return v;
}


/*Description:
 * this function outputs the tanh function f(z) = (e^z-e^-z)/(e^z+e^-z)
 * 
 * Input:
 * 		@double z: indipendent element z
 * Output:
 * 		@double f(z) = (e^z-e^-z)/(e^z+e^-z)
 * */
double
single_element_tanh_function (double z)
{
  return (exp (z) - exp (-z)) / (exp (z) + exp (-z));
}


/*Description:
 * this function outputs the tanh function f(z) = (e^z-e^-z)/(e^z+e^-z) for each element in vector z
 * 
 * Input:
 * 		@double* z: vector of inputs
 * 		@int len: length of the vector z
 * Output:
 * 		@double* v: vector where each element is given by v[i] = f(z[i]) = (e^z[i]-e^-z[i])/(e^z[i]+e^-z[i])
 * */
double *
vector_element_tanh_function (double *z, int len)
{
  int i;
  double *v = (double *) malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    {
      v[i] = (exp (z[i]) - exp (-z[i])) / (exp (z[i]) + exp (-z[i]));
    }
  return v;
}


/*Description:
 * this function outputs the tanh function f(z) = (e^z-e^-z)/(e^z+e^-z) for each element in matrix z
 * 
 * Input:
 * 		@double** z: matrix of inputs
 * 		@int rows: rows of the matrix z
 * 		@int cols: columns of the matrix z
 * Output:
 * 		@double** v: matrix where each element is given by v[i][j] = f(z[i][j]) = (e^z[i][j]e^-z[i][j])/(e^z[i][j]+e^-z[i][j])
 * */
double **
matrix_element_tanh_function (double **z, int rows, int cols)
{
  int i, j;
  double **v = (double **) malloc (sizeof (double *) * rows);
  for (i = 0; i < rows; i++)
    {
      v[i] = (double *) malloc (sizeof (double) * cols);
      for (j = 0; j < cols; j++)
	{
	  v[i][j] =
	    (exp (z[i][j]) - exp (-z[i][j])) / (exp (z[i][j]) +
						exp (-z[i][j]));
	}
    }
  return v;
}


/*Description:
 * this function outputs the ranh derivative function f(z) = 1-tanh(z)^2 for z
 * 
 * Input:
 * 		@double z: indipendent input element
 * Output:
 * 		@double f(z): 1-tanh(z)^2
 * */
double
single_element_tanh_derivative_function (double z)
{
  double val = single_element_tanh_function (z);
  return 1 - (val * val);
}


/*Description:
 * this function outputs the tanh derivative function f(z) = 1-tanh(z)^2 for each element in vector z
 * 
 * Input:
 * 		@double* z: input vector
 * 		@int len: length of the vector z
 * Output:
 * 		@double* v: vector where each element is given by v[i] = f(z[i]) = 1-tanh(z[i])^2
 * */
double *
vector_element_tanh_derivative_function (double *z, int len)
{
  int i;
  double val;
  double *v = (double *) malloc (sizeof (double) * len);
  for (i = 0; i < len; i++)
    {
      val = single_element_tanh_function (z[i]);
      v[i] = 1 - (val * val);
    }
  return v;
}

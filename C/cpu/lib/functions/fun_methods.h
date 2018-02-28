#ifndef __FUN_METHODS_H__
#define __FUN_METHODS_H__


/* defined in math_functions.c*/
double drand ();
double random_normal ();
double random_general_gaussian (double mean, double dev);


/*defined in cost_functions.c*/
double *vector_element_quadratic_cost_derivative (double *target,
						  double *output, int len);
double *vector_element_cross_entropy_cost_derivative_formOne (double *target,
							      double *output,
							      int len);
double *vector_element_cross_entropy_cost_derivative_formTwo (double *target,
							      double *output,
							      int len);
double
  *vector_element_cross_entropy_formOne_derivative_with_softmaxOutputLayer
  (double *target, double *output, int len);


/*defined in activation_functions.c*/
double single_element_tanh_function (double z);
double single_element_tanh_derivative_function (double z);
double single_element_sigmoid_derivative_function (double z);
double single_element_sigmoid_function (double z);
double single_element_Relu_function (double z);
double single_element_Relu_derivative_function (double z);
double **matrix_element_tanh_function (double **z, int rows, int cols);
double **matrix_element_softmax_function (double **z, int rows, int cols);
double **matrix_element_Relu_derivative_function (double **z, int rows,
						  int cols);
double **matrix_element_Relu_function (double **z, int rows, int cols);
double **matrix_element_sigmoid_derivative_function (double **z, int rows,
						     int cols);
double **matrix_element_sigmoid_function (double **z, int rows, int cols);
double *vector_element_sigmoid_function (double *z, int len);
double *vector_element_sigmoid_derivative_function (double *z, int len);
double *vector_element_Relu_function (double *z, int len);
double *vector_element_Relu_derivative_function (double *z, int len);
double *vector_element_softmax_function (double *z, int len);
double *vector_element_tanh_function (double *z, int len);
double *vector_element_tanh_derivative_function (double *z, int len);



/*defined in matrix_functions.c*/
double mul (double *v1, double *v2, int len);
int free_matrix (double **m, int rows);
double *from_matrix_to_vector (double **m, int rows, int cols);
double *mul1D (double **w, double *v, int rows, int cols);
double *vector_sum (double *v1, double *v2, int len);
double *dot (double *v1, double *v2, int len);
double **transpose (double **m, int rows, int cols);
double **from_vector_to_matrix (double *v, int rows, int cols);
double **mul2D_caching_one (double **m1, double **m2, int rows1, int cols1,
			    int cols2);
double **mul2D_caching_two (double **m1, double **m2, int rows1, int cols1,
			    int cols2);
double *dot2D (double **v1, double **v2, int rows, int cols);
double matrix_sum (double **v1, int rows, int cols);


#endif

#ifndef __FUL_METHODS_H__
#define __FUL_METHODS_H__

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


/*defined in init.c*/
double **fully_connected_layer_weights_init (int input_neurons,
					     int output_neurons);
FeedElem *feed_forward_for_fully_connected_layer (double *x, double **w,
						  double *b,
						  int input_neurons,
						  int output_neurons,
						  int flag);
BackElem *backpropagation_for_fully_connected_layer (double *error,
						     double **weights,
						     double *input, double *z,
						     int rows, int cols,
						     int flag, int len);
BackElem *backpropagation_output_for_fully_connected_layer (double *target,
							    double *input,
							    double *z,
							    double *a,
							    int input_neurons,
							    int
							    output_neurons,
							    int flag1,
							    int flag2);

#endif

#ifndef __SET_METHODS_H__
#define __SET_METHODS_H__

/* functions defined in set_options.c*/
int shuffle_training_set_in_vector (double **m, int n);
double *ann_biases_init (int len);
int load_set_in_double_vector (char *file, double *v, int *len);
int load_set_in_int_vector (char *file, int *v, int *len);
int load_set_in_short_int_vector (char *file, short int *v, int *len);
int load_set_in_char_vector (char *file, char *v, int *len);

#endif

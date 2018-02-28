#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*defined in math_functions.c*/
double random_normal ();


/*Description
 * given a vector and its lengths this function shuffle the indices of the vector in a random way
 * Input:
 * 		@double** m: vector
 * 		@int n: length of the vector
 * Output:
 * 		@int 0
 * */
int
shuffle_training_set_in_vector (double **m, int n)
{
  if (n > 1)
    {
      size_t i;
      for (i = 0; i < n - 1; i++)
	{
	  size_t j = i + rand () / (RAND_MAX / (n - i) + 1);
	  double *t = m[j];
	  m[j] = m[i];
	  m[i] = t;
	}
      return 0;
    }


/*Description:
 * returns a vector of len length with len biases intialized
 * Input:
 * 		@int len: number of neurons for a layer
 * Output:
 * 		double* b: the vector of biases for a layer
 * */
  double *ann_biases_init (int len)
  {
    int i;
    double *b = (double *) malloc (sizeof (double) * len);
    for (i = 0; i < len; i++)
      {
	b[i] = random_normal ();
      }

    return b;
  }



/*Description:
 * given a file_path and a double vector of size 1 this function loads from the binary file
 * each 8 bytes as a double, return 0 if error doesn't occur and 1 if occurs
 * 
 * Input:
 * 		@char* file: file_path.bin
 * 		@double* v: vector of values
 * 		@int* len: length of the vector v at the end
 * Output:
 * 		@int 0: error doesn't occur
 * 		@int 1: error occurs
 * */
  int load_set_in_double_vector (char *file, double *v, int *len)
  {

    double bytes[1];
    int i;
    FILE *f = fopen (file, "rb");

    if (f == NULL)
      return 1;

    for (i = 0; fread (bytes, sizeof (double), 1, f) != 0; i++)
      {

	v = (double *) realloc (v, sizeof (double) * (i + 1));

	v[i] = bytes[0];



      }
    *len = i;
    if (feof (f))
      {
	i = fclose (f);
	if (i)
	  return 1;
	return 0;
      }
    fclose (f);
    return 1;
  }





/*Description:
 * given a file_path and a int vector of size 1 this function loads from the binary file
 * each 4 bytes as an int, return 0 if error doesn't occur and 1 if occurs
 * 
 * Input:
 * 		@char* file: file_path.bin
 * 		@int* v: vector of values
 * 		@int* len: length of the vector v at the end
 * Output:
 * 		@int 0: error doesn't occur
 * 		@int 1: error occurs
 * */
  int load_set_in_int_vector (char *file, int *v, int *len)
  {
    int bytes[1];
    int i;
    FILE *f = fopen (file, "rb");

    if (f == NULL)
      return 1;

    for (i = 0; fread (bytes, sizeof (int), 1, f) != 0; i++)
      {

	v = (int *) realloc (v, sizeof (int) * (i + 1));

	v[i] = bytes[0];
      }
    *len = i;
    if (feof (f))
      {
	i = fclose (f);
	if (i)
	  return 1;
	return 0;
      }
    fclose (f);
    return 1;
  }



/*Description:
 * given a file_path and a short int vector of size 1 this function loads from the binary file
 * each 2 bytes as a short int, return 0 if error doesn't occur and 1 if occurs
 * 
 * Input:
 * 		@char* file: file_path.bin
 * 		@short int* v: vector of values
 * 		@int len: length of the vector v at the end
 * Output:
 * 		@int 0: error doesn't occur
 * 		@int 1: error occurs
 * */
  int load_set_in_short_int_vector (char *file, short int *v, int *len)
  {
    short int bytes[1];
    int i;
    FILE *f = fopen (file, "rb");

    if (f == NULL)
      return 1;

    for (i = 0; fread (bytes, sizeof (short int), 1, f) != 0; i++)
      {

	v = (short int *) realloc (v, sizeof (short int) * (i + 1));

	v[i] = bytes[0];
      }
    *len = i;
    if (feof (f))
      {
	i = fclose (f);
	if (i)
	  return 1;
	return 0;
      }
    fclose (f);
    return 1;
  }




/*Description:
 * given a file_path and a char vector of size 1 this function loads from the binary file
 * each 1 byte as a char, return 0 if error doesn't occur and 1 if occurs
 * 
 * Input:
 * 		@char* file: file_path.bin
 * 		@char* v: vector of values
 * 		@int len: length of the vector v at the end
 * Output:
 * 		@int 0: error doesn't occur
 * 		@int 1: error occurs
 * */
  int load_set_in_char_vector (char *file, char *v, int *len)
  {
    char bytes[1];
    int i;
    FILE *f = fopen (file, "rb");

    if (f == NULL)
      return 1;

    for (i = 0; fread (bytes, sizeof (char), 1, f) != 0; i++)
      {

	v = (char *) realloc (v, sizeof (char) * (i + 1));

	v[i] = bytes[0];
      }
    *len = i;
    if (feof (f))
      {
	i = fclose (f);
	if (i)
	  return 1;
	return 0;
      }
    fclose (f);
    return 1;
  }
